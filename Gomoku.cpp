//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Gomoku.res");
USEFORM("UnitMain.cpp", FormMain);
USEFORM("UnitConnect.cpp", FormConnect);
USEFORM("UnitConnecting.cpp", FormConnecting);
USEFORM("UnitSelect.cpp", FormSelect);
USEFORM("UnitAbout.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Gomoku";
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormConnect), &FormConnect);
		Application->CreateForm(__classid(TFormConnecting), &FormConnecting);
		Application->CreateForm(__classid(TFormSelect), &FormSelect);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
