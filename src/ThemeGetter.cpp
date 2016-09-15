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

	//RefPtr<CssProvider> theme = CssProvider::get_named("Mint-X-Purple", "");

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
	styleCtx->add_provider(theme, GTK_STYLE_PROVIDER_PRIORITY_THEME);
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

  // some pango text
  auto layout = Pango::Layout::create(cr);
  layout->set_text("Hello World!");
  layout->set_font_description(styleCtx->get_font());
  //layout->set_font_description(Pango::FontDescription("Noto Sans 10"));
  int tw, th;
  layout->get_pixel_size(tw, th);


  const int h = 36;
  const int w = 80;


	// normal
	styleCtx->set_state(StateFlags::STATE_FLAG_NORMAL);
	layout->set_font_description(styleCtx->get_font());
	styleCtx->render_background(cr, 200, 200, w, h);
	styleCtx->render_frame(cr, 200, 200, w, h);
	styleCtx->render_layout(cr, 200+ ((w - tw)/2), 200 + ((h - th) /2), layout);

	// +focus
	styleCtx->set_state(StateFlags::STATE_FLAG_FOCUSED);
	layout->set_font_description(styleCtx->get_font());
	styleCtx->render_background(cr, 200, 300, w, h);
	styleCtx->render_frame(cr, 200, 300, w, h);
	styleCtx->render_focus(cr, 200, 300, w, h);
	styleCtx->render_layout(cr, 200+ ((w - tw)/2), 300 + ((h - th) /2), layout);

	// +hover
	styleCtx->set_state(StateFlags::STATE_FLAG_FOCUSED | StateFlags::STATE_FLAG_PRELIGHT);
	layout->set_font_description(styleCtx->get_font());
	styleCtx->render_background(cr, 200, 400, w, h);
	styleCtx->render_frame(cr, 200, 400, w, h);
	styleCtx->render_focus(cr, 200, 400, w, h);
	styleCtx->render_layout(cr, 200+ ((w - tw)/2), 400 + ((h - th) /2), layout);


	// +active
	styleCtx->set_state(StateFlags::STATE_FLAG_SELECTED | StateFlags::STATE_FLAG_PRELIGHT | StateFlags::STATE_FLAG_ACTIVE );
	layout->set_font_description(styleCtx->get_font());
	styleCtx->render_background(cr, 200, 500, w, h);
	styleCtx->render_frame(cr, 200, 500, w, h);
	styleCtx->render_focus(cr, 200, 500, w, h);
	styleCtx->render_layout(cr, 200+ ((w - tw)/2), 500 + ((h - th) /2), layout);


	// let's see what we've done
	cs->write_to_png("/home/andy/out.png");
	return 0;
}
