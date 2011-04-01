#include <QtCore/QObject>

#include "RulesXmlHandler.h"
#include "RootNode.h"
#include "ActionNode.h"
#include "StorageNode.h"
#include "EmotionNode.h"
#include "ConditionNode.h"
#include "ConditionPerceptionNode.h"
#include "ConditionEmotionNode.h"
#include "ConditionDataMiningNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RulesXmlHandler::RulesXmlHandler( Brain* brain) :
		QXmlDefaultHandler(),
		_rootNode( NULL ),
		_currentNode( NULL ),
		_parentNode( NULL ),
		_brain( brain ),
		_parentObject( new QObject(0) )
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

		if( QString::compare( qName, "Rules", Qt::CaseInsensitive ) == 0 )
		{
			return createRootNode( atts );
		}
		else if( QString::compare( qName, "Condition", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionNode( atts );
		}
		else if( QString::compare( qName, "Action", Qt::CaseInsensitive ) == 0 )
		{
			return createActionNode( atts );
		}
		else if( QString::compare( qName, "Storage", Qt::CaseInsensitive ) == 0 )
		{
			return createStorageNode( atts );
		}
		else if( QString::compare( qName, "Emotion", Qt::CaseInsensitive ) == 0 )
		{
			return createEmotionNode( atts );
		}

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

	/*
		Creates a root node. It can only exist 1 root node.
	*/
	bool RulesXmlHandler::createRootNode(  const QXmlAttributes & atts )
	{
		Q_UNUSED( atts );

		// it can only exist 1 root node.
		if( _rootNode != NULL )
		{
			return false;
		}

		_rootNode = new RootNode( _brain, _parentObject );
		_currentNode = _rootNode;

		return true;
	}

	bool RulesXmlHandler::createActionNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "key" );
		QString value = atts.value( "value" );

		_parentNode = _currentNode;
		_currentNode =  new ActionNode( key, value, _brain, _parentNode );

		return true;

	}

	bool RulesXmlHandler::createStorageNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "key" );
		QString value = atts.value( "value" );
		Brain::MemoryType memory = Brain::translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;
		_currentNode =  new StorageNode( key, value, memory, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createEmotionNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "key" );
		QString value = atts.value( "value" );

		bool okMin;
		int min = atts.value( "min" ).toInt(&okMin);
		bool okMax;
		int max = atts.value( "max" ).toInt(&okMax);

		if(!okMax)
		{
			max = INT_MAX;
		}
		if(!okMin)
		{
			min = INT_MIN;
		}

		_parentNode = _currentNode;
		_currentNode =  new EmotionNode( key, value, max, min, _brain, _parentNode );

		return true;
	}

	/*

	*/
	bool RulesXmlHandler::createConditionNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		if( atts.index( "perception") != -1)
		{
			return createConditionPerceptionNode( atts );
		}
		else if( atts.index( "datamining" ) != -1)
		{
			return createConditionDataMiningNode( atts );
		}
		else if( atts.index( "emotion" ) != -1 )
		{
			return createConditionEmotionNode( atts );
		}

		return false;
	}

	/*

	*/
	bool RulesXmlHandler::createConditionPerceptionNode(  const QXmlAttributes & atts )
	{
		QString key = atts.value( "perception" );
		QString value = atts.value( "value" );
		QString opString = atts.value( "operator" );
		ConditionNode::ConditionOperator op = ConditionNode::translateConditionOperator( opString );

		_parentNode = _currentNode;
		_currentNode =  new ConditionPerceptionNode( key, value, op, _brain, _parentNode );

		return true;

	}

	/*

	*/
	bool RulesXmlHandler::createConditionEmotionNode(  const QXmlAttributes & atts )
	{
		QString key = atts.value( "emotion" );
		QString value = atts.value( "value" );
		ConditionNode::ConditionOperator op = ConditionNode::translateConditionOperator( atts.value( "operator" ) );

		_parentNode = _currentNode;
		_currentNode =  new ConditionEmotionNode( key, value, op, _brain, _parentNode );

		return true;
	}

	/*

	*/
	bool RulesXmlHandler::createConditionDataMiningNode(  const QXmlAttributes & atts )
	{
		QString key = atts.value( "event" );
		QString value = atts.value( "value" );
		ConditionNode::ConditionOperator op = ConditionNode::translateConditionOperator( atts.value( "operator" ) );
		ConditionNode::DataMiningOperation opDataMining = ConditionNode::translateDataMiningOperator( atts.value( "datamining" ) );
		Brain::MemoryType memory = Brain::translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;
		_currentNode =  new ConditionDataMiningNode( key, value, op, opDataMining, memory, _brain, _parentNode );

		return true;
	}


}
