#include "MyForm.h"

using namespace System;
using namespace SplittingPolygon;

void WinMain() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MyForm^ form = gcnew MyForm();
    Application::Run(form);
}