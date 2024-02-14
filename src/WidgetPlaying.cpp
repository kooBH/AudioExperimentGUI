#include "WidgetPlaying.h"


WidgetPlaying::WidgetPlaying(QWidget* parent) : QWidget(parent) {
  setStyleSheet("\
			QWidget{background:rgb(229, 251, 223);}\
      \
      ");

  layout_main.setAlignment(Qt::AlignLeft);
  layout_main.addWidget(&widget_player);

  btn_mute_all.setText("mute");
  btn_unmute_all.setText("unmute");
  layout_mute.addWidget(&btn_mute_all);
  layout_mute.addWidget(&btn_unmute_all);
  layout_speakers.addLayout(&layout_mute);

  layout_speakers.setAlignment(Qt::AlignTop);
  layout_main.addLayout(&layout_speakers);

  setLayout(&layout_main);

  QObject::connect(&widget_player.le_channels, &QLineEdit::textChanged, this, &WidgetPlaying::slot_channels);
  QObject::connect(this, &WidgetPlaying::signal_audio_probe, &widget_player, &WidgetPlayer::slot_audio_probe);
  QObject::connect(&widget_player.btn_audioprobe, &QPushButton::pressed, [&] {this->AudioProbe(); });
  QObject::connect(&widget_player.btn_load_sample, &QPushButton::pressed, this, &WidgetPlaying::slot_load_sample);
  QObject::connect(this, &WidgetPlaying::signal_set_sample, &widget_player, &WidgetPlayer::slot_set_sample);

  // Temp
  SetSpeaker(8);
  widget_player.pb_play.setMaximum(100);
  widget_player.pb_play.setValue(55);
}



WidgetPlaying::~WidgetPlaying() {
  ReleaseSpeaker();
}

int WidgetPlaying::SetSpeaker(int n_spk_) {
  ReleaseSpeaker();
  n_spk = n_spk_;
  for (int i = 0; i < n_spk; i++) {
    WidgetSpeaker* tmp = new WidgetSpeaker(i);
    vector_speaker.push_back(tmp);
    layout_speakers.addWidget(tmp);
  }
  return n_spk;
}

void WidgetPlaying::ReleaseSpeaker() {
  for (auto& tmp : vector_speaker) {
    delete tmp;
  }
  vector_speaker.clear();
  n_spk = 0;
}

void WidgetPlaying::slot_channels(QString str) {
  bool is_valid;
  int n_channels_ = str.toInt(&is_valid);
  if (!is_valid)
    n_channels = 0;
  else
    n_channels = n_channels_;
  printf("WidgetPlaying;:n_channels : %d\n",n_channels);
  if (n_channels != 0) {
    ReleaseSpeaker();
    SetSpeaker(n_channels);
  }
}

void WidgetPlaying::slot_load_sample() {
  QString filename = QFileDialog::getOpenFileName(this, "Open Sample", QDir::homePath(), "Wav Files (*.wav)");
  if (filename.isEmpty()) {
    return;
  }
  widget_player.label_sample.setText(filename);
  path_sample = filename;
  emit signal_set_sample(filename);
}

void WidgetPlaying::AudioProbe() {
  map_device.clear();
  map_speaker.clear();

  text_device = " *** Device List *** \n\n";
  // Create an api map.
  std::map<int, std::string> apiMap;
  apiMap[RtAudio::MACOSX_CORE] = "OS-X Core Audio";
  apiMap[RtAudio::WINDOWS_ASIO] = "Windows ASIO";
  apiMap[RtAudio::WINDOWS_DS] = "Windows Direct Sound";
  apiMap[RtAudio::WINDOWS_WASAPI] = "Windows WASAPI";
  apiMap[RtAudio::UNIX_JACK] = "Jack Client";
  apiMap[RtAudio::LINUX_ALSA] = "Linux ALSA";
  apiMap[RtAudio::LINUX_PULSE] = "Linux PulseAudio";
  apiMap[RtAudio::LINUX_OSS] = "Linux OSS";
  apiMap[RtAudio::RTAUDIO_DUMMY] = "RtAudio Dummy";

  RtAudio audio;
  RtAudio::DeviceInfo info;
  text_device.append("Current API : ");
  text_device.append(
    QString::fromStdString(apiMap[audio.getCurrentApi()]));
  text_device.append("\n\n");

  unsigned int devices = audio.getDeviceCount();

  //text_device = "";

  /* Create Widgets */
  for (unsigned int i = 0; i < devices; i++) {
    info = audio.getDeviceInfo(i);
    QString temp_device = "[";
    temp_device.append(QString::fromStdString(to_string(i)));
    temp_device.append("]");
    // QString name_dev = QString::fromLocal8Bit(info.name.c_str());
     //QString name_dev = QString::fromUtf8(info.name.c_str());
    temp_device.append(QString::fromStdString(info.name));
    // temp_device.append(name_dev);
    // std::cout<<"device name " << info.name<<"\n";
    map_device.insert(make_pair(temp_device.toStdString(), i));

    text_device.append(temp_device);

    text_device.append("\n");
    if (info.probed == false) {
      text_device.append("Probe Status = Unsuccessful");
      text_device.append("\n");
    }
    else {
      //  std::cout << "Probe Status = Successful\n";
      text_device.append("Output Channels = ");
      text_device.append(
        QString::fromStdString(to_string(info.outputChannels)));

      if (info.outputChannels != 0) {
        map_speaker.insert(make_pair(temp_device.toStdString(), i));
      }

      text_device.append("\nInput Channels = ");
      text_device.append(
        QString::fromStdString(to_string(info.inputChannels)));

      text_device.append("\n");
      if (info.sampleRates.size() < 1) {
        text_device.append("No supported sample rates found!");
      }
      else {
        text_device.append("Supported sample rates = ");
        for (unsigned int j = 0; j < info.sampleRates.size(); j++) {
          text_device.append(QString::fromStdString(
            to_string(info.sampleRates[j])
          ));
          text_device.append(" ");
        }
      }
      text_device.append("\n");
    }
    text_device.append("\n");
  }
  text_device.append("\n");

  emit(signal_audio_probe(text_device));
  
  /* Set Speaker's device list*/

  for (auto spk : vector_speaker) {
    spk->cb_speaker.clear();
    for (auto& dev : map_speaker) {
      spk->cb_speaker.addItem(QString::fromStdString(dev.first));
    }
  }

}

void WidgetPlaying::init_renderer() {
}

void WidgetPlaying::start_rendering() {

}

void WidgetPlaying::release_renderer() {
}