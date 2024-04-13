#pragma once

#include "scene/Scene.h"
#include "util/note/Note.h"
#include "util/ChordType.h"
#include "util/scale/Scale.h"
#include "gui/menu-item/MenuItem.h"

class ChordScene : public Scene
{
private:
  Note root;
  Scale *scale;
  ChordType chordType;
  const int STARTING_KEY_Y = 40;
  const int WHITE_KEY_WIDTH = 8; 
  const int WHITE_KEY_HEIGHT = 20;
  const int BLACK_KEY_WIDTH = 5; 
  const int BLACK_KEY_HEIGHT = 12; 
  MenuItem *connectedMenuItem;
  MenuItem *rootMenuItem;
  MenuItem *scaleMenuItem;
  static const Note MIN_NOTE = NOTE_C1;
  static const Note MAX_NOTE = NOTE_C7;
  static void onKnobLeft(int count, void *usr_data);
  static void onKnobRight(int count, void *usr_data);
  void toggleScale();

public:
  ChordScene(Squidbox *squidbox);
  void init() override;
  void update() override;
  void playChord(int index, bool on);
};
