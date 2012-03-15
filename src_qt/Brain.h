#if !defined(_BRAIN_H)
#define _BRAIN_H

#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QList>
#include <QtCore/QSemaphore>
#include <QtCore/QQueue>

#include "CnotiMind_global.h"
#include "Perception.h"
#include "Emotion.h"
#include "MemoryEvent.h"
#include "CnotiMind.h"
//#include "rules/ConditionNode.h"

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
	class MemoryXmlHandler;
	class ActionModifier;

	class BrainGUI;


	class CNOTIMIND_EXPORT Brain: public QThread
	{
		Q_OBJECT

	public:

		enum BrainNodes
		{
			EmotionNodes,
			ActionNodes,
			UndefinedNodes
		};

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
		bool loadXmlActionModifiers( const QString& filename );

		bool saveMemory(const QString& filename);
		bool loadMemory(const QString& filename);
		bool saveEmotionalStateToMemory();
		bool loadEmotionalStateFromMemory();
		bool saveLastSceneToMemory();
		bool loadLastSceneFromMemory();
		void run();

		// Methods to clear brain state
		void clearWorkingMemory();
		void clearMemory();

		// Methods for printing brain data in console
		void printSettings();
		void printRules();
		void printMemory( MemoryType type );
		void printProperties();

		// Friend classes Nodes
		friend class ActionNode;
		friend class ClearMemoryNode;
		friend class ConditionNode;
		friend class ConditionEmotionNode;
		friend class ConditionDataMiningNode;
		friend class ConditionPerceptionNode;
		friend class ConditionVariableNode;
		friend class ConditionPropertyNode;
		friend class DataMiningNode;
		friend class DeleteNode;
		friend class EmotionNode;
		friend class MathOperationNode;
		friend class MemoryXmlHandler;
		friend class PropertyNode;
		friend class RuleNode;
		friend class RootNode;
		friend class StorageNode;
		friend class StorageCopyNode;
		friend class DisableNode;

		// Friend class Models
		friend class EmotionsModel;
		friend class MemoryModel;
		friend class PerceptionsModel;
		friend class PropertiesModel;

	public slots:
		void receivePerception(const Perception& perception);
		void stop();
		void showGUI();

	signals:
		void sendAction( const QString& key, const QString& value );
		void sendEmotionalState(const QString& emotion, qreal value);

	private:
		void updateGUI();

		// Methods to update the emotional state
		void updateEmotionalValue(const QString& emotionName, qreal variation, qreal max, qreal min);
		void updateEmotionalValue(const QString& emotionName, qreal variation);
		void setEmotionalValue(const QString &emotionName, qreal value);

		Emotion* findEmotion(const QString& emotionName);
		void emotionChanged(const Emotion* emotion);

		// Methods to update a property
		void updatePropertyValue( const QString& name, const QString& value );

		// Methods to store information in memory
		void storeToMemory( const MemoryEvent& event, MemoryType memory );

		void executeAction( const QString& key, const QString& value );

		void deleteEvent( const QString& key, EventPosition position, MemoryType memory );
		void deleteEvent( const QString& key, const QString& value, EventPosition position, MemoryType memory );

		void copyEvents( MemoryType fromMemory, MemoryType toMemory );
		void copyEvents( MemoryType fromMemory, MemoryType toMemory, const QString afterEvent,
						 EventPosition afterPosition, const QString &beforeEvent,
						 EventPosition beforePosition);

		int findMemoryEvent( EventPosition position, const QString& eventName, const QList<MemoryEvent>& memory );
		int findMemoryEvent( int itemPosition, const QString& eventName, const QList<MemoryEvent>& memory );

		// Methods to get information from the memory
		QVariant dataMining( DataMiningOperation operation, const QString& event, int position, MemoryType memoryType, bool *valid = NULL );
		QVariant dataMining( DataMiningOperation operation, const QString& event, const QString& value, int position, MemoryType memoryType, bool *valid = NULL );
		QVariant dataMining( DataMiningOperation operation, const QString& event, qreal value, int position, MemoryType memoryType, bool *valid = NULL );

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
		QString dataMiningItem( const QString& event, int position, const QList<MemoryEvent>& memory, bool *valid = NULL );

		qreal dataMiningTime( const QString& event, const QList<MemoryEvent>& memory, bool *valid = NULL );
		qreal dataMiningTime( const QString& event, const QString& value, const QList<MemoryEvent>& memory, bool *valid = NULL );

//		QString dataMiningDuration( const QString& event, const QList<MemoryEvent>& memory );
//		QString dataMiningTime( const QString& event, const QList<MemoryEvent>& memory );

		// method to help set valid value
		inline void setValid( bool* valid, bool value );

		void deactivateTask(const QString& task);
		void activateTask(const QString& task);
		BrainNodes translateBrainTasks( const QString& text );

		QList<ActionModifier*> actionModifiers(const QString& action);

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
		QHash<QString, QString> _properties;
		int _timerDecayEmotions;

		bool _quit;

		BrainGUI *_gui;

		QList<BrainNodes> _disabledTasks;	// List with the brain activities that are disabled.
		QList<ActionModifier*> _actionModifiers;
		bool _talkModifierEnabled;	// TODO: in the future maybe necessary to think a better way, so it can handle all the actions.

        // Hold action info
        typedef struct {
            QString key;
            QString value;
        } action;
    };

}
#endif  //_BRAIN_H
