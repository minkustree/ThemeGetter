/*
 ============================================================================
 Name        : ThemeGetter.cpp
 Author      : Andy Clark
 Version     :
 Copyright   : Copyright (C) 2016 Andy Clark
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include <gtkmm.h>

using namespace std;
using namespace Glib;
using namespace Gtk;

int main(int argc, char* argv[]) {
	cout << "Hello World" << endl; /* prints Hello World */

	Main main(argc, argv);

	//RefPtr<CssProvider> theme = CssProvider::get_named("HighContrast", "");

	//StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), theme, GTK_STYLE_PROVIDER_PRIORITY_THEME);

	// Set up a our rendering surface & context
	Cairo::RefPtr<Cairo::ImageSurface> cs = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, 800, 600);
	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(cs);

	// Fill background
	cr->rectangle(0, 0, 800, 600);
	cr->set_source_rgb(0.7,0.7,0.9);
	cr->fill();

	// Get theme and set up a styling context
	RefPtr<CssProvider> theme = CssProvider::get_default();
	RefPtr<StyleContext> styleCtx = StyleContext::create();
	styleCtx->add_provider(theme, GTK_STYLE_PROVIDER_PRIORITY_FALLBACK);
	styleCtx->set_screen(Gdk::Screen::get_default());

	// internal dimensions
	int x = 0 + 25; //margin.get_left();
	int y = 0 + 25; //margin.get_top();
	int width = 800 - 50; //margin.get_left() - margin.get_right();
	int height = 600 - 50; //margin.get_top() - margin.get_bottom();

	// render background
	WidgetPath wwp;
	wwp.path_append_type(Window::get_type());
	wwp.iter_add_class(-1, "background");
	styleCtx->set_path(wwp);
	styleCtx->render_background(cr, x, y, width, height);
	styleCtx->render_frame(cr, x, y, width, height);

	// render some button-like thing
	WidgetPath bwp;
	bwp.path_append_type(Button::get_type());
	bwp.iter_add_class(-1, "button");
	styleCtx->set_path(bwp);

	// normal
	styleCtx->set_state(StateFlags::STATE_FLAG_NORMAL);
	styleCtx->render_background(cr, 200, 200, 80, 24);
	styleCtx->render_frame(cr, 200, 200, 80, 24);

	// focus
	styleCtx->set_state(StateFlags::STATE_FLAG_FOCUSED);
	styleCtx->render_background(cr, 200, 300, 80, 24);
	styleCtx->render_frame(cr, 200, 300, 80, 24);
	styleCtx->render_focus(cr, 200, 300, 80, 24);

	// active
	styleCtx->set_state(StateFlags::STATE_FLAG_FOCUSED | StateFlags::STATE_FLAG_ACTIVE);
	styleCtx->render_background(cr, 200, 400, 80, 24);
	styleCtx->render_frame(cr, 200, 400, 80, 24);
	styleCtx->render_focus(cr, 200, 400, 80, 24);

	// some cairo toy-rendered text
	cr->move_to(400, 200);
	cr->set_source_rgb(0.1, 0.1, 0.1);
	cr->select_font_face("Noto Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
	cr->set_font_size(10);
	cr->show_text("Hello World!");

	// some pango text
	cr->move_to(400, 400);
	auto layout = Pango::Layout::create(cr);
	layout->set_text("Hello World!");
	layout->set_font_description(Pango::FontDescription("Noto Sans 10"));
	layout->show_in_cairo_context(cr);

	// let's see what we've done
	cs->write_to_png("/home/andy/out.png");
	return 0;
}
