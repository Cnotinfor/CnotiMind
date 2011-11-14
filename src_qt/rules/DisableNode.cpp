#include "DisableNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	DisableNode::DisableNode( const QString& task, const QString& value, Brain* brain, QObject* parent ):
		RuleNode( brain, parent ),
		_nodeName( task )
	{
		if (value.compare("false", Qt::CaseInsensitive ) == 0)
		{
			_toDisable = false;
		}
		else
		{
			_toDisable = true;
		}
	}

	void DisableNode::exec()
	{
		if (_toDisable)
		{
			_brain->deactivateTask(_nodeName);
		}
		else
		{
			_brain->activateTask(_nodeName);
		}
	}

	void DisableNode::exec(QHash<QString, QString>& variables)
	{
		Q_UNUSED(variables);

		this->exec();
	}

	QString DisableNode::info(int depth) const
	{
		QString info;

		info += space(depth) + "Disable (" + _nodeName + ") value=" + _toDisable;

		return info + RuleNode::info(depth);
	}

}	// CnotiMind


