#include <CGUI.hh>

using namespace CGui;

static void reveal_entry_on_click(Button* sender, Label* label, Revealer* revealer, Revealer* revealer1, Revealer* revealer2, Revealer* revealer3)
{
	if (!revealer->Reveal())
		revealer->Reveal(true);
	if (!revealer1->Reveal())
		revealer1->Reveal(true);
	if (!revealer2->Reveal())
		revealer2->Reveal(true);
	if (!revealer3->Reveal())
		revealer3->Reveal(true);

	label->Hide();
	sender->Hide();
}

static void submited(Button* sender, Entry* email, Entry* passwd)
{
	std::cout << "Email:    " << email->Text() << std::endl;
	std::cout << "Password: " << passwd->Text() << std::endl;
}

int main(int argc, char* argv[])
{
	Init init(argc, argv);

	CssProvider cssProvider("style.css", Priority::APPLICATION);

	Window window(WindowType::TOPLEVEL, "Window", WindowPos::CENTER);
	window.AddStyleClass("window");

	Headerbar headerbar("Window");
	headerbar.ShowCloseButton(false);
	headerbar.AddStyleClass("headerbar");
	headerbar.HasSubTitle(false);
	Button close_button;
	close_button.AlwaysShowImage(true);
	close_button.AddStyleClass("close_button");
	Pixbuf close_pixbuf("close.png", 10, 10, false);
	Image close_image(close_pixbuf);
	close_image.Align(Alignments::FILL, Alignments::FILL);
	close_button.ButtonImage(close_image);
	close_button.Clicked(CGui::MainQuit);

	headerbar.AddEnd(close_button);
	window.CustomHeaderbar(headerbar);

	Box main_vbox(Orientation::VERTICAL, 5); // First vbox
	main_vbox.Align(Alignments::FILL, Alignments::FILL);

	Box vbox(Orientation::VERTICAL, 10); // Second vbox
	vbox.Align(Alignments::CENTER, Alignments::CENTER);

	// Second vbox
	Box signin_label_vbox(Orientation::VERTICAL, 10);
	Revealer signin_label_revealer(RevealerTransition::CROSSFADE, 200);
	Label signin_label("SIGN UP");
	signin_label.AddStyleClass("signin_label");
	signin_label.Selectable(false);
	signin_label.Justify(Justification::FILL);
	signin_label.SingleLineMode(true);
	signin_label_revealer.Add(signin_label);
	signin_label_vbox.CenterWidget(signin_label_revealer);

	Box email_hbox(Orientation::HORIZONTAL, 0);
	Revealer email_revealer(RevealerTransition::SLIDE_RIGHT, 300);
	email_revealer.Reveal(false);
	email_revealer.Align(Alignments::BEGIN, Alignments::CENTER);
	Entry email_entry("Email");
	email_entry.AddStyleClass("email_entry");
	email_entry.SizeRequest(300, 0);
	email_entry.MaxLength(30);
	email_entry.ProgressFraction(1.0);
	email_entry.GrabFocusWithoutSelecting();
	email_revealer.Add(email_entry);
	email_hbox.CenterWidget(email_revealer);

	Box passwd_hbox(Orientation::HORIZONTAL, 0);
	Revealer passwd_revealer(RevealerTransition::SLIDE_LEFT, 300);
	passwd_revealer.Reveal(false);
	passwd_revealer.Align(Alignments::LAST, Alignments::CENTER);
	Entry passwd_entry("Password");
	passwd_entry.Visibility(false);
	passwd_entry.AddStyleClass("passwd_entry");
	passwd_entry.SizeRequest(300, 0);
	passwd_entry.MaxLength(12);
	passwd_entry.ProgressFraction(1.0);
	passwd_revealer.Add(passwd_entry);
	passwd_hbox.CenterWidget(passwd_revealer);

	Box signin_vbox(Orientation::VERTICAL, 0);
	Revealer signin_revealer(RevealerTransition::SLIDE_DOWN, 500);
	signin_revealer.Reveal(false);
	signin_revealer.Align(Alignments::CENTER, Alignments::CENTER);
	Button signin_button("Submit");
	signin_button.AddStyleClass("signin_button");
	signin_button.SizeRequest(200, 0);
	signin_button.Clicked(submited, email_entry, passwd_entry);
	signin_revealer.Add(signin_button);
	signin_vbox.CenterWidget(signin_revealer);

	vbox.AddStart(signin_label_vbox);
	vbox.AddStart(email_hbox);
	vbox.AddStart(passwd_hbox);
	vbox.AddEnd(signin_vbox);

	// First vbox
	Label amazing_label("Let's get started, Press START to continue.");
	amazing_label.Align(Alignments::CENTER, Alignments::CENTER);
	amazing_label.AddStyleClass("amazing_label");
	amazing_label.Justify(Justification::CENTER);
	amazing_label.Selectable(false);
	amazing_label.SingleLineMode(true);

	Button start_button("START");
	start_button.Align(Alignments::CENTER, Alignments::CENTER);
	start_button.AddStyleClass("start_button");
	start_button.Clicked(reveal_entry_on_click, amazing_label, email_revealer, passwd_revealer, signin_revealer, signin_label_revealer);

	main_vbox.AddStart(amazing_label);
	main_vbox.AddStart(start_button);
	main_vbox.CenterWidget(vbox);

	window.Add(main_vbox);
	window.DefaultSize(853, 480);
	window.InternalWidth(10);
	window.Resizable(false);
	window.ShowAll();
	return 0;
}