#ifndef BRAINGUI_H
#define BRAINGUI_H

#include <QWidget>
#include "../Perception.h"

namespace Ui {
	class BrainGUI;
}

namespace CnotiMind
{
	class Brain;
	class PropertiesModel;
	class EmotionsModel;
	class PerceptionsModel;
	class MemoryModel;
	class ActionsModel;


	class BrainGUI : public QWidget
	{
		Q_OBJECT

	public:
		BrainGUI( const Brain* brain, QWidget *parent = 0);
		~BrainGUI();

	public slots:
		void updateProperties();
		void updateEmotions();
		void updatePerceptions( const Perception& p );
		void updateLongTermMemory();
		void updateWorkingMemory();
		void updateActions( const QString& key, const QString& value );

	protected:
		void changeEvent(QEvent *e);

	private:
		Ui::BrainGUI*      _ui;
		PropertiesModel*   _propertiesModel;
		EmotionsModel*     _emotionsModel;
		PerceptionsModel*  _perceptionsModel;
		MemoryModel*       _longTermMemoryModel;
		MemoryModel*       _workingMemoryModel;
		ActionsModel*      _actionsModel;
	};

}
#endif // BRAINGUI_H
