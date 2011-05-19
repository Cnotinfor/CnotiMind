#ifndef BRAINGUI_H
#define BRAINGUI_H

#include <QWidget>

namespace Ui {
	class BrainGUI;
}

namespace CnotiMind
{
	class Brain;
	class PropertiesModel;

	class BrainGUI : public QWidget
	{
		Q_OBJECT

	public:
		BrainGUI( const Brain* brain, QWidget *parent = 0);
		~BrainGUI();

	public slots:
		void updateProperties();

	protected:
		void changeEvent(QEvent *e);

	private:
		Ui::BrainGUI*      _ui;
		PropertiesModel*   _propertiesModel;
	};

}
#endif // BRAINGUI_H
