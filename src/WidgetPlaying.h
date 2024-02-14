#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>


#include <map>
#include <vector>
#include <string>
using std::string;
using std::to_string;
using std::map;

#include "WidgetPlayer.h"
#include "WidgetSpeaker.h"
#include "RtBase.h"



class WidgetPlaying : public QWidget {
  Q_OBJECT

private:
  QHBoxLayout layout_main;
  WidgetPlayer widget_player;
 
  QVBoxLayout layout_speakers;
  QHBoxLayout layout_mute;
  QPushButton btn_mute_all;
  QPushButton btn_unmute_all;
  std::vector<WidgetSpeaker*> vector_speaker;

  int n_spk = 0;
  int n_channels = 0;
  int samplerate = 0;

  map<string, unsigned int> map_device;
  map<string, unsigned int> map_speaker;
  QString text_device;

  QString path_sample;

  short** buf_play;
  int n_hop;

  void init_renderer();
  void start_rendering();
  void release_renderer();

public:
  WidgetPlaying(QWidget* parent = 0);
  ~WidgetPlaying();

  int SetSpeaker(int n_spk);
  void ReleaseSpeaker();
  void AudioProbe();

signals : 
  void signal_audio_probe(QString text);
  void signal_set_sample(QString text);

public slots:
  void slot_channels(QString str);
  void slot_load_sample();
};