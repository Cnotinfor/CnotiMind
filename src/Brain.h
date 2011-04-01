#if !defined(_BRAIN_H)
#define _BRAIN_H

#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QList>
#include <QtCore/QSemaphore>
#include <QtCore/QQueue>

#include "CnotiMind_global.h"
#include "Action.h"
#include "Perception.h"
#include "Emotion.h"
#include "MemoryEvent.h"


namespace CnotiMind
{

	class RuleNode;
	class ActionNode;
	class StorageNode;
	class EmotionNode;
	class ConditionNode;
	class ConditionPerceptionNode;
	class ConditionEmotionNode;
	class ConditionDataMiningNode;


	class CNOTIMIND_EXPORT Brain: public QThread
	{
		Q_OBJECT

	public:

		enum MemoryType
		{
			LongTermMemory,
			WorkingMemory,
			UndefinedMemory
		};

		Q_ENUMS( MemoryType )

		Brain(const QString& path, QObject* parent);
		Brain(QObject* parent);

		// Methods to set up the brain
		bool loadXmlSettings( const QString& filename );
		void addValidPerception( const QString& perception );
		void addValidAction( const QString& action );
		void addEmotion( const Emotion& Emotion );
		bool loadXmlRules( const QString& filename );



		bool validateXML(int xml);
		bool saveMemory(const QString& filename);
		bool loadMemory(const QString& filename);
		bool saveEmotionalState(const QString& filename);
		bool loadEmotionalState(const QString& filename);
		void run();

		// Methods to clear brain state
		void clearWorkingMemory();
		void clearMemory();

		// Methods for printing brain data in console
		void printSettings();
		void printRules();
		void printMemory( MemoryType type );

		// Friend classes
		friend class RuleNode;
		friend class RootNode;
		friend class ActionNode;
		friend class StorageNode;
		friend class EmotionNode;
		friend class ConditionNode;
		friend class ConditionEmotionNode;
		friend class ConditionDataMiningNode;
		friend class ConditionPerceptionNode;

	public:
		static MemoryType translateMemoryType( const QString& text );

	public slots:
		void receivePerception(const Perception& perception);

	signals:
		void sendAction( const QString& key, const QString& value );
		void sendEmotionalState(const QString& emotion, int value);

	private:

		// Methods to update the emotional state
		void updateEmotionalValue(const QString& emotionName, int variation, int max, int min);
		void updateEmotionalValue(const QString& emotionName, int variation);

		// Methods to store information in memory
		void storeToMemory( const MemoryEvent& event, MemoryType memory );

		void executeAction( const QString& key, const QString& value );



	private:
		RuleNode* _rules;
		QList<QString> _validPerceptions;
		QList<QString> _validActions;
		QList<Emotion> _emotions;
		QSemaphore _semaphoreBrain;
		QQueue<Perception> _receivedPerceptions;
		QQueue<QString> _emotionsChanged;
		QList<MemoryEvent> _longTermMemory;
		QList<MemoryEvent> _workingMemory;
		int _timerDecayEmotions;
	};

}
#endif  //_BRAIN_H
