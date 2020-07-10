#include <CGUI.hh>

using namespace CGui;

static void ForwardNext(CheckButton* sender, MessageDialog* dialog, Assistant* assistant, Box* page)
{
	if (sender->Checked())
	{
		auto response = dialog->Run();
		if (response == ResponseType::YES)
		{
			assistant->PageComplete(*page, true);
			dialog->Hide();
		}
		else if (response == ResponseType::NO)
		{
			assistant->PageComplete(*page, false);
			dialog->Hide();
			sender->Checked(false);
		}
	}
	else
		assistant->PageComplete(*page, false);
}

static void Installation_Confirm(Entry* sender, Assistant* assistant, Box* page)
{
	if (sender->TextLength() >= 1)
		assistant->PageComplete(*page, true);
	else
		assistant->PageComplete(*page, false);
}

int main(int argc, char* argv[])
{
	Init init(argc, argv);

	CssProvider cssProvider("style.css", Priority::APPLICATION);

	Assistant assistant;
	assistant.AddStyleClass("assistant");

	Handler el(&assistant);
	el.SignalHandler(Signals::CANCEL, CGui::MainQuit);

	// Get Started Page
	Label first_label("Press Next to continue.\nThis is the demo for Assistant");
	assistant.AppendPage(first_label);
	assistant.PageTitle(first_label, "Get Started");
	assistant.PageType(first_label, AssistantPageType::INTRO);
	assistant.PageComplete(first_label, true);

	// Terms and conditions page
	MessageDialog ask_dialog(*dynamic_cast<Window*>(&assistant), DialogFlags::DESTORY_WITH_PARENT, MessageType::QUESTION, ButtonsType::YES_NO);
	ask_dialog.SecondaryText("Do you accept the terms and conditions ?");
	ask_dialog.Decorated(false);
	ask_dialog.DefaultSize(200, 100);
	Box vbox(Orientation::VERTICAL, 10);
	Label accept_terms("This is the terms and conditions....");
	CheckButton accept_button("Accept terms and conditions");
	accept_button.Toggled(ForwardNext, ask_dialog, assistant, vbox);
	vbox.CenterWidget(accept_terms);
	vbox.AddEnd(accept_button);
	assistant.AppendPage(vbox);
	assistant.PageTitle(vbox, "Terms and Conditions");
	assistant.PageType(vbox, AssistantPageType::INTRO);

	// Installation page
	Box l_vbox(Orientation::VERTICAL, 10);
	Entry path("Path");
	path.Align(Alignments::FILL, Alignments::FILL);
	path.Changed(Installation_Confirm, assistant, l_vbox);
	l_vbox.CenterWidget(path);
	assistant.AppendPage(l_vbox);
	assistant.PageTitle(l_vbox, "Installtion Path");
	assistant.PageType(l_vbox, AssistantPageType::CONTENT);

	assistant.Position(WindowPos::CENTER);
	assistant.DefaultSize(640, 480);
	assistant.ShowAll();

	return 0;
}