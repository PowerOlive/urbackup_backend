/*************************************************************************
*    UrBackup - Client/Server backup system
*    Copyright (C) 2011-2015 Martin Raiber
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU Affero General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*
*    You should have received a copy of the GNU Affero General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include "TreeNode.h"

#include <memory.h>
#include <string.h>

TreeNode::TreeNode(const char* name, const char* data, TreeNode *parent)
	: name(name), data(data), parent(parent), num_children(0), nextSibling(NULL), mapped_node(NULL),
	  subtree_changed(false)
{
}

TreeNode::TreeNode(void)
	: num_children(0), nextSibling(NULL), mapped_node(NULL), subtree_changed(false), parent(NULL),
	name(NULL), data(NULL)
{
}

std::string TreeNode::getName()
{
	if(name)
	{
		return name;
	}
	else
	{
		return std::string();
	}
}

std::string TreeNode::getData()
{
	if(data!=NULL)
	{
		return std::string(data, data+c_treenode_data_size);
	}
	else
	{
		return std::string();
	}
}

void TreeNode::setName(const char* pName)
{
	name=pName;
}

void TreeNode::setData(const char* pData)
{
	data=pData;
}

size_t TreeNode::getNumChildren()
{
	return num_children;
}

TreeNode* TreeNode::getFirstChild(void)
{
	if(num_children>0)
	{
		return this+1;
	}
	else
	{
		return NULL;
	}
}

void TreeNode::setNextSibling(TreeNode *pNextSibling)
{
	nextSibling=pNextSibling;
}

void TreeNode::incrementNumChildren(void)
{
	++num_children;
}

void TreeNode::setId(size_t pId)
{
	id=pId;
}

size_t TreeNode::getId(void) const
{
	return id;
}

TreeNode *TreeNode::getNextSibling(void)
{
	return nextSibling;
}

TreeNode* TreeNode::getChild(size_t n)
{
	TreeNode *firstChild=getFirstChild();
	size_t i=0;
	while(firstChild!=NULL && i!=n)
	{
		firstChild=firstChild->getNextSibling();
		++i;
	}
	if(i==n)
	{
		return firstChild;
	}
	else
	{
		return NULL;
	}
}

void TreeNode::setParent(TreeNode *pParent)
{
	parent=pParent;
}

TreeNode *TreeNode::getParent(void)
{
	return parent;
}

TreeNode *TreeNode::getMappedNode()
{
	return mapped_node;
}

void TreeNode::setMappedNode(TreeNode *pMappedNode)
{
	mapped_node=pMappedNode;
}

void TreeNode::setSubtreeChanged( bool b )
{
	subtree_changed=b;
}

bool TreeNode::getSubtreeChanged()
{
	return subtree_changed;
}

bool TreeNode::nameEquals( const TreeNode& other )
{
	if(name!=NULL && other.name!=NULL)
	{
		return strcmp(name, other.name)==0;
	}
	else
	{
		return name==other.name;
	}
}

bool TreeNode::dataEquals( const TreeNode& other )
{
	if(data!=NULL && other.data!=NULL)
	{
		return memcmp(data, other.data, c_treenode_data_size)==0;
	}
	else
	{
		return data==other.data;
	}
}

bool TreeNode::equals( const TreeNode& other )
{
	return nameEquals(other) &&
		dataEquals(other);
}
