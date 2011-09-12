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
		explicit RulesXmlHandler(Brain* brain, RuleNode* rootNode = NULL);
		~RulesXmlHandler();

		bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
		bool endElement( const QString & namespaceURI, const QString & localName, const QString & qName );

		RuleNode* rootNode() const;

		int line() const;

	protected:


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
