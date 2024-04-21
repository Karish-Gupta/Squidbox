#include "ChordScene.h"
#include "Squidbox.h"

ChordScene::ChordScene(Squidbox *squidbox) : Scene(squidbox, nullptr) {
  type = CHORD_SCENE;
  chordType = TRIAD;

  rootMenuItem = new RootNoteMenuItem();
  scaleMenuItem = new ScaleMenuItem();

  MenuItem **menuItems = new MenuItem *[2];
  menuItems[0] = rootMenuItem;
  menuItems[1] = scaleMenuItem;

  menu = new Menu("Chords", 2, menuItems, MAIN_SCENE);

  keyboard = new Keyboard(squidbox);
}

void ChordScene::init() { Scene::init(); }

void ChordScene::update() {
  Scene::update();

  // Check if any of the buttons are pressed
  for (int i = 0; i < NUM_BUTTONS; i++) {
    Button *button = squidbox->getButton(i);
    if (squidbox->getButton(i)->isPressed()) {
      playChord(i, true);
    } else if (squidbox->getButton(i)->isReleased()) {
      playChord(i, false);
    }
  }

  // Update keyboard
  keyboard->update(rootMenuItem->getRootNote());
}

void ChordScene::playChord(int index, bool on) {
  // TODO: Fix bug where switching root while chord playing causes notes to hang
  Scale *scale = scaleMenuItem->getScale();
  Note root = rootMenuItem->getRootNote();
  int *notes = scale->getNotesFromChord(root, index, chordType);
  for (int i = 0; i < chordType.numNotes; i++) {
    keyboard->setKeyDown(notes[i], on);
    if (on) {
      MIDIServer::noteOn(0, notes[i], 127);
    } else {
      MIDIServer::noteOff(0, notes[i], 127);
    }
  }
}