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
#include "CnotiMind.h"
#include "rules/ConditionNode.h"



namespace CnotiMind
{

	class RuleNode;
	class ActionNode;
	class StorageNode;
	class EmotionNode;
	//class ConditionNode;
	class ConditionPerceptionNode;
	class ConditionEmotionNode;
	class ConditionDataMiningNode;


	class CNOTIMIND_EXPORT Brain: public QThread
	{
		Q_OBJECT

	public:



		Q_ENUMS( MemoryType )

		Brain(const QString& path, QObject* parent);
		Brain(QObject* parent);

		~Brain();

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
		friend class EmotionNode;
		friend class DataMiningNode;
		friend class StorageNode;
		friend class ConditionNode;
		friend class ConditionEmotionNode;
		friend class ConditionDataMiningNode;
		friend class ConditionPerceptionNode;

	public:

	public slots:
		void receivePerception(const Perception& perception);
		void stop();

	signals:
		void sendAction( const QString& key, const QString& value );
		void sendEmotionalState(const QString& emotion, qreal value);

	private:

		// Methods to update the emotional state
		void updateEmotionalValue(const QString& emotionName, qreal variation, qreal max, qreal min);
		void updateEmotionalValue(const QString& emotionName, qreal variation);

		// Methods to store information in memory
		void storeToMemory( const MemoryEvent& event, MemoryType memory );

		void executeAction( const QString& key, const QString& value );

		// Methods to get information from the memory
		QVariant dataMining( DataMiningOperation operation, const QString& event, MemoryType memoryType, bool *valid = NULL );
		QVariant dataMining( DataMiningOperation operation, const QString& event, const QString& value, MemoryType memoryType, bool *valid = NULL );
		QVariant dataMining( DataMiningOperation operation, const QString& event, qreal value, MemoryType memoryType, bool *valid = NULL );

		qreal dataMiningMax( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningMin( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningSum( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningSum( const QString& event, qreal value, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningCount( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningCount( const QString& event, const QString& value, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningMean( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );

		bool dataMiningExists( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		bool dataMiningExists( const QString& event, const QString& value, const QList<MemoryEvent>& memory, bool *valid = NULL );

		QString dataMiningLast( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		QString dataMiningFirst( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );

//		QString dataMiningDuration( const QString& event, const QList<MemoryEvent>& memory );
//		QString dataMiningTime( const QString& event, const QList<MemoryEvent>& memory );

		// method to help set valid value
		inline void setValid( bool* valid, bool value );

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

		bool _quit;
	};

}
#endif  //_BRAIN_H
