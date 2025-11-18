First solution:
My implementation is in (Tree.hpp) https://github.com/Jsyn14/CS372-Final-Exam-Programming-Component/blob/main/Tree.hpp

as
template <typename T, typename Compare> SmartList<T> fringe(Tree<T,Compare> const& tree);
located near the bottom of the file, directly after the prune function.

Second solution: 
My solution for comparing two trees to determine whether they have the same fringe is implemented in:

Tree.hpp — see the standalone function:
template <typename T, typename Compare> bool hasSameFringe(const Tree<T,Compare>& a, const Tree<T,Compare>& b);
This function is located immediately after the fringe function.
