#include "WidgetPlayer.h"

WidgetPlayer::WidgetPlayer(QWidget* parent) : QWidget(parent) {
  setStyleSheet("\
			QWidget{background:rgb(250, 230, 232);}\
      \
      ");

  setFixedWidth(256);

  label.setText("WidgetPlayer");
  layout_main.addWidget(&label);

  layout_main.addWidget(&pb_play);

  btn_play.setText("Play!");
  layout_main.addWidget(&btn_play);

  label_channels.setText("Speaker");
  le_channels.setText("8");
  layout_channels.addWidget(&label_channels);
  layout_channels.addWidget(&le_channels);
  layout_main.addLayout(&layout_channels);

  label_samplerate.setText("Samplerate");
  cb_samplerate.addItem("16000");
  cb_samplerate.addItem("48000");
  layout_samplerate.addWidget(&label_samplerate);
  layout_samplerate.addWidget(&cb_samplerate);
  layout_main.addLayout(&layout_samplerate);

  btn_dir.setText("Dir");
  label_dir.setText("empty");
  layout_dir.addWidget(&btn_dir);
  layout_dir.addWidget(&label_dir);
  layout_main.addLayout(&layout_dir);

  btn_load_sample.setText("LoadSample");
  btn_play_sample.setText("PlaySample");
  layout_sample.addWidget(&btn_load_sample);
  layout_sample.addWidget(&btn_play_sample);
  //layout_sample.addWidget(&cb_sample);
  layout_sample.addWidget(&label_sample);
  layout_main.addLayout(&layout_sample);

  btn_audioprobe.setText("AudioProbe");
  layout_main.addWidget(&btn_audioprobe);
  layout_main.addWidget(&tb_audioprobe);

  setLayout(&layout_main);
}

WidgetPlayer::~WidgetPlayer() {
}

void WidgetPlayer::slot_audio_probe(QString text){
  tb_audioprobe.clear();
  tb_audioprobe.append(text);
}

void WidgetPlayer::slot_set_sample(QString text) {
  label_sample.setText(text);
  label_sample.setToolTip(text);
}
