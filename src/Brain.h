#if !defined(_BRAIN_H)
#define _BRAIN_H

#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QList>
#include <QtCore/QSemaphore>

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
	class ConditionEventNode;
	class ConditionEmotionNode;
	class ConditionDataMiningNode;


	class Brain: QThread
	{
		Q_OBJECT

	public:

		enum MemoryType
		{
			LongTermMemory,
			WorkingMemory
		};

		Q_ENUMS( MemoryType )

		Brain(const QString& path, QObject* parent);
		Brain(QObject* parent);

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
		void clearWorkingMemory();
		void clearMemory();
		void sendAction(const Action& action);
		void sendEmotionalState(const QString& state, int value);
		void receivePerception(const Perception& perception);

		bool createRules(int xml);
		RuleNode* createNode(int xml, RuleNode* parent);
		ActionNode* createActionNode(int xml, RuleNode* parent);
		StorageNode* createStorageNode(int xml, RuleNode* parent);
		EmotionNode* createEmotionNode(int xml, RuleNode* parent);
		ConditionNode* createConditionNode(int xml, RuleNode* parent);
		ConditionEventNode* createConditionEventNode(int xml, RuleNode* parent);
		ConditionEmotionNode* createConditionEmotionNode(int xml, RuleNode* parent);
		ConditionDataMiningNode* createConditionDataMiningNode(int xml, RuleNode* parent);

		void updateEmotionalState(const QString& state, int variation, int max, int min);
		void updateEmotionalState(const QString& state, int variation);

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


	private:
		RuleNode* _rules;
		QList<QString> _validPerceptions;
		QList<QString> _validActions;
		QList<Emotion> _emotions;
		QSemaphore _semaphorePerceptions;
		QList<Perception> _receivedPerceptions;
		QList<MemoryEvent> _longTermMemory;
		QList<MemoryEvent> _workingMemory;
		int _timerDecayEmotions;
	};

}
#endif  //_BRAIN_H
