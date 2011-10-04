#ifndef RULESXMLHANDLER_H
#define RULESXMLHANDLER_H

#include <QXmlDefaultHandler>

class QObject;

namespace CnotiMind
{
	class RuleNode;
	class RootNode;
	class ActionNode;
	class StorageNode;
	class EmotionNode;
	class ConditionNode;
	class ConditionPerceptionNode;
	class ConditionEmotionNode;
	class ConditionDataMiningNode;
	class Brain;

	class RulesXmlHandler : public QXmlDefaultHandler
	{

	public:
		explicit RulesXmlHandler(Brain* brain, RuleNode* _rules = NULL);
		~RulesXmlHandler();

		bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
		bool endElement( const QString & namespaceURI, const QString & localName, const QString & qName );

		RuleNode* rootNode() const;

		int line() const;

	protected:
		bool createRootNode( const QXmlAttributes & atts );
		bool createActionNode( const QXmlAttributes & atts );
		bool createStorageNode( const QXmlAttributes & atts );
		bool createStorageCopyNode( const QXmlAttributes & atts );
		bool createEmotionNode( const QXmlAttributes & atts );
		bool createDataMiningNode( const QXmlAttributes & atts );
		bool createConditionNode( const QXmlAttributes & atts );
		bool createConditionPerceptionNode( const QXmlAttributes & atts );
		bool createConditionVariableNode( const QXmlAttributes & atts );
		bool createConditionPropertyNode( const QXmlAttributes & atts );
		bool createConditionEmotionNode( const QXmlAttributes & atts );
		bool createConditionDataMiningNode( const QXmlAttributes & atts );
		bool createMathOperationNode( const QXmlAttributes & atts );
		bool createPropertyNode( const QXmlAttributes & atts );
		bool createDeleteNode( const QXmlAttributes & atts );
		bool createClearMemoryNode( const QXmlAttributes & atts );
		bool createRandomNode( const QXmlAttributes & atts );

	protected:
		RuleNode* _rootNode;
		RuleNode* _currentNode;
		RuleNode* _parentNode;
		Brain* _brain;

		QObject* _parentObject; // Parent of the RootNode

		int _line;
	};

}
#endif // RULESXMLHANDLER_H
