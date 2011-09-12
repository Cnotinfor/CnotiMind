#if !defined(_RULENODE_H)
#define _RULENODE_H

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtXml/QXmlAttributes>

#include "../Node.h"

namespace CnotiMind
{

	class Brain;

	/*!
		The RuleNode class is the base of all rules nodes of the brain.

		The Brain has several rules build using RuleNode objects. The RuleNode objects are
		organized in a tree structure.

		Each class that extends RuleNode should implement a static method called fromXML, which converts
		XML attributes to a RuleNode*. If it is not possible to create that node, that it should
		return NULL.

		The method should then be called in the class RulesXmlHandler, method startElement.

		Method prototype:
		static RuleNode *fromXML( const QString &qName, const QXmlAttributes &atts, QObject* parent )
	*/
	class RuleNode : public QObject
	{
		Q_OBJECT


	public:


		RuleNode( Brain* brain, QObject* parent );

		/*!
			Method call to execute the RuleNode. The method must be reimplemented.
		*/
		virtual void exec() = 0;

		/*!
			Method call to execute the RuleNode. The method must be reimplemented.

			It receives the variables available to be used, if they are necessary.

			\sa tagsToValue
		*/
		virtual void exec( QHash<QString, QString>& variables ) = 0;

		/*!
		   By default the nodes are not root nodes. For all the tree, there is only one RootNode

		   \sa RootNode
		*/
		virtual bool isRoot() const;

		/*!
			Method to show the information of the node in a QString. Must be reimplemented in
			the subclasses.
		*/
		virtual QString info( int depth = 0 ) const = 0;

	protected:
		/*!
			Method to execute the children RuleNode from the current node. If there are no children
			it doesn't do nothing.
		*/
		virtual void execChildren();

		/*!
			Method to execute the children RuleNode from the current node. If there are no children
			it doesn't do nothing.
		*/
		virtual void execChildren( QHash<QString, QString> &variables );

		/*!
			Replaces tags in the string value. The tags replaced are variables and properties.

			Properties are identified by curl brackets, while variables are identified
			by square brackets.
		*/
		void tagsToValue( QString& value, const QHash<QString, QString>& variables );

		/*!
			Depending on the depth is adds space. used by the info method to represent visually
			the node, while printing the tree nodes.
		*/
		QString space( int depth ) const;

	protected:
		Brain* _brain;
	};

}
#endif  //_RULENODE_H
