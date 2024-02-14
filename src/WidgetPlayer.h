#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QProgressBar>

class WidgetPlayer : public QWidget {
  Q_OBJECT

public:
  QVBoxLayout layout_main;
  QLabel label;
  QProgressBar pb_play;

  QPushButton btn_play;

  QHBoxLayout layout_channels;
  QLabel label_channels; 
  QLineEdit le_channels;

  QHBoxLayout layout_samplerate;
  QLabel label_samplerate;
  QComboBox cb_samplerate;

  QHBoxLayout layout_dir;
  QPushButton btn_dir;
  QLabel label_dir;

  QHBoxLayout layout_sample;
  QPushButton btn_load_sample;
  QPushButton btn_play_sample;
  //QComboBox cb_sample;
  QLabel label_sample;

  QPushButton btn_audioprobe;
  QTextBrowser tb_audioprobe;

  WidgetPlayer(QWidget* parent = 0);
  ~WidgetPlayer();

public slots:
    void slot_audio_probe(QString text);
    void slot_set_sample(QString text);
};