#include <QtCore/QObject>
#include <QDebug>

#include "RulesXmlHandler.h"
#include "RootNode.h"
#include "ActionNode.h"
#include "StorageNode.h"
#include "EmotionNode.h"
#include "ConditionNode.h"
#include "ConditionPerceptionNode.h"
#include "ConditionEmotionNode.h"
#include "ConditionDataMiningNode.h"
#include "ConditionVariableNode.h"
#include "DataMiningNode.h"
#include "MathOperationNode.h"
#include "PropertyNode.h"
#include "ConditionPropertyNode.h"
#include "DeleteNode.h"
#include "ClearMemoryNode.h"
#include "RandomNode.h"
#include "../Brain.h"

#define DO_NOTHING qDebug() << "Nothing"

namespace CnotiMind
{

	RulesXmlHandler::RulesXmlHandler(Brain* brain, RuleNode* rootNode) :
		QXmlDefaultHandler(),
		_rootNode( rootNode ),
		_currentNode( NULL ),
		_parentNode( rootNode ),
		_brain( brain ),
		_parentObject( new QObject(0) ),
		_line( 0 )
	{
	}

	RulesXmlHandler::~RulesXmlHandler()
	{
		delete _parentObject;
	}


	bool RulesXmlHandler::startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts )
	{
		Q_UNUSED( namespaceURI );
		Q_UNUSED( localName );

		_line++;
		RuleNode *node;

		qDebug()<< "[RulesXmlHandler::startElement]" << qName;

		// RootNode is child from parentNode, to ensure that if the getRootNode is not called
		// All the nodes created by XML are released.
		node = RootNode::fromXML(qName, atts, _brain, _parentObject);
		if( _rootNode == NULL && node != NULL )
		{
			_parentNode = _currentNode = _rootNode = node;
			return true;
		}
		else if( _parentNode != NULL && _currentNode != NULL)
		{
			if( node = ActionNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = ClearMemoryNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = ConditionDataMiningNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = ConditionEmotionNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = ConditionPerceptionNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = ConditionPropertyNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = ConditionVariableNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = DataMiningNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = DeleteNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = EmotionNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = MathOperationNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = PropertyNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = RandomNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;
			else if( node = StorageNode::fromXML(qName, atts, _brain, _currentNode) ) DO_NOTHING;

			qDebug()<< "[RulesXmlHandler::startElement]" << "done";
			// If a node was created then update some variables
			if( node != NULL )
			{
				_parentNode = _currentNode;
				_currentNode = node;
				return true;
			}
		}

		qDebug() << "[RulesXmlHandler::startElement] Invalid element" << qName;
		return false;
	}

	/*
		When an element is closed the currentNode and parentNode are updated
	*/
	bool RulesXmlHandler::endElement( const QString & namespaceURI, const QString & localName, const QString & qName )
	{
		Q_UNUSED( namespaceURI );
		Q_UNUSED( localName );
		Q_UNUSED( qName );

		qDebug()<< "[RulesXmlHandler::endElement]" << qName;

		if( _rootNode == _currentNode )
		{
			_currentNode = NULL;
			return true;
		}

		_currentNode = _parentNode;
		_parentNode = qobject_cast<RuleNode*>( _currentNode->parent() );

		return true;
	}

	/*
		Return the RootNode from the rules. Who calls this will be responsible for freeing
		the memory of the Rules.
	*/
	RuleNode* RulesXmlHandler::rootNode() const
	{
		// removes the handler has parent, so who calls now must be responsible for deleting all nodes
		_rootNode->setParent( 0 );

		return _rootNode;
	}

	int RulesXmlHandler::line() const
	{
		return _line;
	}
}
