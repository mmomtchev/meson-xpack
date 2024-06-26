#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <windows.h>
#include <delayimp.h>
#include <libloaderapi.h>
#include <wchar.h>

char mypath[4096];

void ErrorExit(const char *fn) {
  char *error;
  DWORD dw = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&error, 0, NULL);

  fprintf(stderr, "%s: %s\n", fn, error);
  ExitProcess(dw);
}

/*
 * This is as close as one get can to an -rpath on Windows:
 * https://devblogs.microsoft.com/oldnewthing/20170126-00/?p=95265
 */

#pragma comment(lib, "delayimp")

HMODULE LoadPython() {
  static char path[4096];
  const char *root;
  HMODULE lib;

  root = getenv("npm_package_json");
  if (root == NULL)
    snprintf(path, 4096, "%s\\%s", PYTHON_PATH, PYTHON_DLL);
  else
    snprintf(path, 4096, "%s\\..\\%s\\%s", root, PYTHON_PATH, PYTHON_DLL);
  lib = LoadLibraryA(path);
  if (lib == NULL) {
    DWORD dw = GetLastError();
    ErrorExit(path);
  }
  return lib;
}
FARPROC WINAPI delayHook(unsigned dliNotify, PDelayLoadInfo pdli) {
  if (dliNotify == dliNotePreLoadLibrary && strcmp(pdli->szDll, PYTHON_DLL) == 0) {
    return (FARPROC)LoadPython();
  }
  return NULL;
}
ExternC const PfnDliHook __pfnDliNotifyHook2 = delayHook;
ExternC const PfnDliHook __pfnDliFailureHook2 = delayHook;

const char freeze[] = "import sys\nsetattr(sys, 'frozen', True)\n";

int main(int argc, char *argv[]) {
  PyStatus status;
  PyConfig config;
  HRSRC hResource = NULL;
  HGLOBAL hMemory = NULL;
  char *text;
  size_t text_len, init_file_len;

  if (argc > 1 && !strcmp(argv[1], "runpython")) {
    text = malloc(sizeof(char) * 4096);
    if (getenv("npm_config_local_prefix") == NULL)
      snprintf(text, 4096, "%s/python.exe", PYTHON_PATH);
    else
      snprintf(text, 4096, "%s/%s/python.exe", getenv("npm_config_local_prefix"), PYTHON_PATH);
    return execvp(text, argv + 1);
  }

  hResource = FindResource(NULL, MAKEINTRESOURCEA(101), "TEXT");
  if (!hResource) {
    ErrorExit("Failed to load the Python code");
  }
  hMemory = LoadResource(NULL, hResource);

  text_len = SizeofResource(NULL, hResource);
  text = LockResource(hMemory);

  GetModuleFileNameA(NULL, mypath, sizeof(mypath));
  init_file_len = strlen(mypath) + strlen("__file__ = r''\n");

  PyConfig_InitPythonConfig(&config);
  config.interactive = 0;

  config.run_command = malloc(sizeof(wchar_t) * (text_len + init_file_len + strlen(freeze) + 1));
  swprintf(config.run_command, init_file_len + text_len + strlen(freeze) + 1, L"__file__ = r'%hs'\n%hs%hs", mypath, freeze, text);

  status = PyConfig_SetBytesArgv(&config, argc, argv);
  if (PyStatus_Exception(status)) {
    goto exception;
  }

  status = Py_InitializeFromConfig(&config);
  if (PyStatus_Exception(status)) {
    goto exception;
  }

  PyConfig_Clear(&config);

  return Py_RunMain();

exception:
  printf("Error\n");
  PyConfig_Clear(&config);
  if (PyStatus_IsExit(status)) {
    return status.exitcode;
  }
  PyErr_Print();
  Py_ExitStatusException(status);
}
