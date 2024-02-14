#include <QWidget>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class WidgetSpeaker : public QWidget {
  Q_OBJECT

private:
  int id_spk = -1;
  std::string path_input;

public:
  QVBoxLayout layout_main;
  QLabel label;
  QHBoxLayout layout_speaker;
  QLabel label_speaker;
  QComboBox cb_speaker;
  QPushButton btn_mute;

  WidgetSpeaker(int id, QWidget* parent = 0);
  ~WidgetSpeaker();
};
