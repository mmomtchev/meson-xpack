#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <wchar.h>
#include <windows.h>
#include <libloaderapi.h>

int main(int argc, char *argv[]) {
  PyStatus status;
  PyConfig config;
  HRSRC hResource = NULL;
  HGLOBAL hMemory = NULL;
  char *text;
  wchar_t *init_file;
  size_t text_len, init_file_len;

  hResource = FindResource(NULL, MAKEINTRESOURCEA(101), "TEXT");
  hMemory = LoadResource(NULL, hResource);

  text_len = SizeofResource(NULL, hResource);
  text = LockResource(hMemory);
  init_file_len = strlen(argv[0]) + strlen("__file__ = r''\n");

  PyConfig_InitPythonConfig(&config);
  config.interactive = 0;

  config.run_command = malloc(sizeof(wchar_t) * (text_len + init_file_len + 1));
  swprintf(config.run_command, init_file_len + text_len + 1, L"__file__ = r'%hs'\n%hs", argv[0], text);

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