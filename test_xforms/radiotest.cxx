#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(367, 198);
    w = o;
    { Fl_Group* o = new Fl_Group(10, 10, 347, 73);
      o->box(FL_DOWN_BOX);
      { Fl_Round_Button* o = new Fl_Round_Button(32, 20, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
        o->setonly();
      }
      { Fl_Round_Button* o = new Fl_Round_Button(32, 45, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Round_Button* o = new Fl_Round_Button(106, 34, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Round_Button* o = new Fl_Round_Button(175, 20, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Round_Button* o = new Fl_Round_Button(175, 58, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Round_Button* o = new Fl_Round_Button(261, 34, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      o->end();
    }
    { Fl_Group* o = new Fl_Group(10, 93, 349, 93);
      o->box(FL_DOWN_BOX);
      { Fl_Round_Button* o = new Fl_Round_Button(280, 103, 64, 20, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
        o->setonly();
      }
      { Fl_Round_Button* o = new Fl_Round_Button(280, 133, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Round_Button* o = new Fl_Round_Button(280, 161, 64, 15, "button");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Group* o = new Fl_Group(10, 93, 89, 93);
        { Fl_Round_Button* o = new Fl_Round_Button(20, 103, 64, 15, "button");
          o->type(102);
          o->down_box(FL_ROUND_DOWN_BOX);
          o->setonly();
        }
        { Fl_Round_Button* o = new Fl_Round_Button(20, 128, 64, 15, "button");
          o->type(102);
          o->down_box(FL_ROUND_DOWN_BOX);
        }
        { Fl_Round_Button* o = new Fl_Round_Button(20, 152, 64, 15, "button");
          o->type(102);
          o->down_box(FL_ROUND_DOWN_BOX);
        }
        o->end();
      }
      o->end();
    }
    o->end();
  }
  w->show(argc, argv);
  return Fl::run();
}
