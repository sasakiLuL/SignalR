#pragma once
#include <memory>
#include <vector>

using std::unique_ptr, std::vector;

namespace SyntacticAnalysis
{
	template<class T>
	class TreeNode
	{
	public:
		TreeNode(const T& data) : _data(data), _branches(vector<unique_ptr<TreeNode<T>>>()) {}
		T getData() const
		{
			return _data;
		}
		inline void insert(unique_ptr<TreeNode<T>> other)
		{
			_branches.push_back(std::move(other));
		}
		const vector<unique_ptr<TreeNode<T>>>& getBranches() const
		{
			return _branches;
		}
	private:
		T _data;
		vector<unique_ptr<TreeNode<T>>> _branches;
	};
}

