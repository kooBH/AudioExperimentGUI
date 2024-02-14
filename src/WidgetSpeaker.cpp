#include "WidgetSpeaker.h"

WidgetSpeaker::WidgetSpeaker(int id_, QWidget* parent) : QWidget(parent) {
  setStyleSheet("\
			QWidget{background:rgb(224, 222, 252);}\
      \
      ");

 id_spk = id_;

  label.setText("WidgetSpeaker");
  layout_main.addWidget(&label);

  label_speaker.setText("speaker_"+QString::number(id_spk));

  layout_speaker.addWidget(&label_speaker);
  layout_speaker.addWidget(&cb_speaker);
  layout_speaker.setAlignment(Qt::AlignLeft);
  cb_speaker.setFixedWidth(128);
  layout_main.addLayout(&layout_speaker);

  btn_mute.setText("Mute");
  btn_mute.setCheckable(true);
  layout_main.addWidget(&btn_mute);

  setLayout(&layout_main);

}

WidgetSpeaker::~WidgetSpeaker() {
}
