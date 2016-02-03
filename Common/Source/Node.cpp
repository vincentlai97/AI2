#include "Node.h"

#include <exception>

Node::Node()
{
}

Node::~Node()
{
	m_childNodes.clear();
}

void Node::AddChild(std::string key, Node* node)
{
	if (m_childNodes.find(key) != m_childNodes.end()) throw new std::exception("Key already exist");

	m_childNodes[key] = node;
	node->parent = this;
}

void Node::RemoveChild(std::string key)
{
	if (m_childNodes.find(key) == m_childNodes.end()) throw new std::exception("Key does not exist");

	m_childNodes.erase(m_childNodes.find(key));
}

std::map<std::string, Node*> Node::GetChildNodes()
{
	return m_childNodes;
}

Node* Node::GetChildNode(std::string key)
{
	if (m_childNodes.find(key) == m_childNodes.end()) throw new std::exception("Key not found");

	return m_childNodes[key];
}

void Node::AddParent(Node* parent)
{
	this->parent = parent;
}

Node* Node::GetParentNode() const
{
	return parent;
}