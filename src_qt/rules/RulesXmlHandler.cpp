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

namespace CnotiMind
{

	RulesXmlHandler::RulesXmlHandler(Brain* brain, RuleNode* rules) :
		QXmlDefaultHandler(),
		_rootNode( rules ),
		_currentNode( NULL ),
		_parentNode( NULL ),
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

		if( QString::compare( qName, "Rules", Qt::CaseInsensitive ) == 0 )
		{
			return createRootNode( atts );
		}
		if( QString::compare( qName, "Condition", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionNode( atts );
		}
		if( QString::compare( qName, "Action", Qt::CaseInsensitive ) == 0 )
		{
			return createActionNode( atts );
		}
		if( QString::compare( qName, "Storage", Qt::CaseInsensitive ) == 0 )
		{
			return createStorageNode( atts );
		}
		if( QString::compare( qName, "Emotion", Qt::CaseInsensitive ) == 0 )
		{
			return createEmotionNode( atts );
		}
		if( QString::compare( qName, "DataMining", Qt::CaseInsensitive ) == 0 )
		{
			return createDataMiningNode( atts );
		}
		if( QString::compare( qName, "MathOperation", Qt::CaseInsensitive ) == 0 )
		{
			return createMathOperationNode( atts );
		}
		if( QString::compare( qName, "Property", Qt::CaseInsensitive ) == 0 )
		{
			return createPropertyNode( atts );
		}
		if( QString::compare( qName, "Delete", Qt::CaseInsensitive ) == 0 )
		{
			return createDeleteNode( atts );
		}
		if( QString::compare( qName, "ClearMemory", Qt::CaseInsensitive ) == 0 )
		{
			return createClearMemoryNode( atts );
		}
		if( QString::compare( qName, "Random", Qt::CaseInsensitive ) == 0 )
		{
			return createRandomNode( atts );
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

	/*
		Creates a root node. It can only exist 1 root node.
	*/
	bool RulesXmlHandler::createRootNode(  const QXmlAttributes & atts )
	{
		Q_UNUSED( atts );

		// it can only exist 1 root node.
		if( _rootNode == NULL )
		{
			_rootNode = new RootNode( _brain, _parentObject );
		}

		_currentNode = _rootNode;

		return true;
	}

	bool RulesXmlHandler::createActionNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "name" );
		QString value = atts.value( "value" );
		QString probability = atts.value( "probability" );

		if( probability.isEmpty() )
		{
			probability = "1";
		}

		_parentNode = _currentNode;
		_currentNode =  new ActionNode( key, value, probability, _brain, _parentNode );

		return true;

	}

	bool RulesXmlHandler::createStorageNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "event" );
		QString value = atts.value( "value" );
		QString clear = atts.value( "clear" );
		MemoryType memory = translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;

		// If the clear attribute is set, it doesn't store the event
		if( QString::compare( clear, "yes", Qt::CaseInsensitive ) == 0)
		{
			_currentNode =  new StorageNode( true, memory, _brain, _parentNode );
		}
		else
		{
			_currentNode =  new StorageNode( key, value, memory, _brain, _parentNode );
		}



		return true;
	}

	bool RulesXmlHandler::createEmotionNode(  const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "name" );
		QString value = atts.value( "increment" );

		bool okMin;
		qreal min = atts.value( "min" ).toDouble(&okMin);
		bool okMax;
		qreal max = atts.value( "max" ).toDouble(&okMax);

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

	bool RulesXmlHandler::createDataMiningNode( const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		QString key = atts.value( "event" );
		QString value = atts.value( "value" );
		DataMiningOperation opDataMining = translateDataMiningOperator( atts.value( "operation" ) );
		QString variable = atts.value( "variable" );
		QString position = atts.value( "position" );
		MemoryType memory = translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;
		_currentNode =  new DataMiningNode( key, value, opDataMining, memory, variable, position, _brain, _parentNode );

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

		QString typeCondition = atts.value( "type" );

		if( QString::compare( typeCondition, "perception", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionPerceptionNode( atts );
		}
		else if( QString::compare( typeCondition, "datamining", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionDataMiningNode( atts );
		}
		else if( QString::compare( typeCondition, "emotion", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionEmotionNode( atts );
		}
		else if( QString::compare( typeCondition, "variable", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionVariableNode( atts );
		}
		else if( QString::compare( typeCondition, "property", Qt::CaseInsensitive ) == 0 )
		{
			return createConditionPropertyNode( atts );
		}

		qDebug() << "[RulesXmlHandler::createConditionNode] Invalid condition node type" << typeCondition;
		return false;
	}

	/*

	*/
	bool RulesXmlHandler::createConditionPerceptionNode(  const QXmlAttributes & atts )
	{
		QString key = atts.value( "perception" );
		QString value = atts.value( "value" );
		ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );

		_parentNode = _currentNode;
		_currentNode =  new ConditionPerceptionNode( key, value, op, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createConditionVariableNode( const QXmlAttributes & atts )
	{
		QString key = atts.value( "variable" );
		QString value = atts.value( "compareValue" );
		ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );

		_parentNode = _currentNode;
		_currentNode =  new ConditionVariableNode( key, value, op, _brain, _parentNode );

		return true;
	}


	bool RulesXmlHandler::createConditionPropertyNode( const QXmlAttributes & atts )
	{
		QString key = atts.value( "property" );
		QString value = atts.value( "compareValue" );
		ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );

		_parentNode = _currentNode;
		_currentNode =  new ConditionPropertyNode( key, value, op, _brain, _parentNode );

		return true;
	}

	/*

	*/
	bool RulesXmlHandler::createConditionEmotionNode(  const QXmlAttributes & atts )
	{
		QString key = atts.value( "emotion" );
		QString value = atts.value( "value" );
		ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );

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
		ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );
		DataMiningOperation opDataMining = translateDataMiningOperator( atts.value( "operation" ) );
		QString variable = atts.value( "variable" );
		QString compareValue = atts.value( "compareValue" );
		MemoryType memory = translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;
		_currentNode =  new ConditionDataMiningNode( key, value, op, opDataMining, memory, variable, compareValue, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createMathOperationNode( const QXmlAttributes & atts )
	{
		if( _rootNode == NULL || _currentNode == NULL )
		{
			return false;
		}

		MathOperation operation = translateMathOperation( atts.value( "name" ) );
		QString value = atts.value( "value" );
		QString variable = atts.value( "variable" );
		QString resultVariable = atts.value( "result" );

		_parentNode = _currentNode;
		_currentNode =  new MathOperationNode( operation, variable, value, resultVariable, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createPropertyNode( const QXmlAttributes & atts )
	{
		QString value = atts.value( "value" );
		QString name = atts.value( "name" );

		_parentNode = _currentNode;
		_currentNode =  new PropertyNode( name, value, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createDeleteNode( const QXmlAttributes & atts )
	{
		QString name = atts.value( "name" );
		QString value = atts.value( "value" );
		DeletePosition position = translateDeletePosition( atts.value( "position" ) ) ;
		MemoryType memory = translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;
		_currentNode =  new DeleteNode( name, value, position, memory, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createClearMemoryNode( const QXmlAttributes & atts )
	{
		MemoryType memory = translateMemoryType( atts.value( "memory" ) );

		_parentNode = _currentNode;
		_currentNode =  new ClearMemoryNode( memory, _brain, _parentNode );

		return true;
	}

	bool RulesXmlHandler::createRandomNode( const QXmlAttributes & atts )
	{
		_parentNode = _currentNode;
		_currentNode =  new RandomNode( _brain, _parentNode );

		return true;
	}

}
