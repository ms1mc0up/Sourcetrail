#include "qt/view/graphElements/QtGraphNodeData.h"

#include "utility/messaging/type/MessageActivateNode.h"
#include "utility/messaging/type/MessageFocusIn.h"
#include "utility/messaging/type/MessageFocusOut.h"
#include "utility/messaging/type/MessageGraphNodeMove.h"

QtGraphNodeData::QtGraphNodeData(const Node* data, bool childVisible)
	: m_data(data)
	, m_childVisible(childVisible)
{
	this->setAcceptHoverEvents(true);

	this->setName(data->getName());
}

QtGraphNodeData::~QtGraphNodeData()
{
}

const Node* QtGraphNodeData::getData() const
{
	return m_data;
}

bool QtGraphNodeData::isDataNode() const
{
	return true;
}

Id QtGraphNodeData::getTokenId() const
{
	return m_data->getId();
}

void QtGraphNodeData::onClick()
{
	if (!m_data->isType(Node::NODE_UNDEFINED | Node::NODE_NAMESPACE))
	{
		MessageActivateNode(m_data->getId(), m_data->getType(), m_data->getFullName()).dispatch();
	}
}

void QtGraphNodeData::moved(const Vec2i& oldPosition)
{
	QtGraphNode::moved(oldPosition);

	MessageGraphNodeMove(m_data->getId(), getPosition() - oldPosition).dispatch();
}

void QtGraphNodeData::updateStyle()
{
	GraphViewStyle::NodeStyle style =
		GraphViewStyle::getStyleForNodeType(m_data->getType(), m_isActive, m_isHovering, m_childVisible);
	setStyle(style);
}

void QtGraphNodeData::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	MessageFocusIn(m_data->getId()).dispatch();
}

void QtGraphNodeData::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	MessageFocusOut(m_data->getId()).dispatch();
}
