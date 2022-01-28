#include <iostream>
#include <vector>
#include <queue>

#include <cassert>

using namespace std;

#ifndef __ListNode__
#define __ListNode__

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

#endif

ListNode* buildList(vector<int>& nums) {
    ListNode dummy;
    ListNode* node = nullptr;;
    auto cur = &dummy;

    for (auto num : nums) {
        node = new ListNode(num);
        cur->next = node;
        cur = cur->next;
    }
    return dummy.next;
}

void destoryList(ListNode* head) {
    auto cur = head;
    while (cur) {
        auto del = cur;
        cur = cur->next;
        delete del;
        del = nullptr;
    }
}

// https://leetcode-cn.com/problems/merge-two-sorted-lists/
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    ListNode dummy;
    auto cur = &dummy;

    while (list1 && list2) {
        if (list1->val < list2->val) {
            cur->next = list1;
            list1 = list1->next;
        } else {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }

    if (list1) cur->next = list1;
    if (list2) cur->next = list2;

    return dummy.next;

}

// https://leetcode-cn.com/problems/merge-k-sorted-lists/
ListNode* mergeKLists(vector<ListNode*>& lists) {

#ifdef ITER
    int size = static_cast<int>(lists.size());
    if (size == 0) return nullptr;
    if (size == 1) return lists[0];

    auto cmp = [](const ListNode* lhs, const ListNode* rhs) {
        if (!lhs || !rhs) return false;
        return lhs->val > rhs->val;
    };

    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);

    ListNode dummy;
    auto cur = &dummy;

    for (auto node : lists) {
        if (node) q.push(node);
    }

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        cur->next = node;
        cur = cur->next;
        if (node->next) {
            q.push(node->next);
        }
    }

    cur->next = nullptr;

    return dummy.next;

#else

    int size = static_cast<int>(lists.size());
    if (size == 0) return nullptr;
    if (size == 1) return lists[0];

    vector<ListNode*> left = vector<ListNode*>(lists.begin(), lists.begin() + (size / 2));
    vector<ListNode*> right = vector<ListNode*>(lists.begin() + (size / 2), lists.end());

    auto leftHead = mergeKLists(left);
    auto rightHead = mergeKLists(right);

    return mergeTwoLists(leftHead, rightHead);

#endif

}

int main(int argc, char* argv[]) {
    vector<int> nums1, nums2, ans;
    nums1 = {1, 2, 4};
    nums2 = {1, 3, 4};
    ans = {1, 1, 2, 3, 4, 4};
    auto list1 = buildList(nums1);
    auto list2 = buildList(nums2);
    auto merge = mergeTwoLists(list1, list2);
    auto cur = merge;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(cur->val == num);
        cur = cur->next;
    }
    destoryList(merge);

    nums1 = {1, 4, 5};
    nums2 = {1, 3, 4};
    vector<int> nums3 = {2, 6};
    ans = {1, 1, 2, 3, 4, 4, 5, 6};
    list1 = buildList(nums1);
    list2 = buildList(nums2);
    auto list3 = buildList(nums3);
    vector<ListNode*> lists = {list1, list2, list3};
    merge = mergeKLists(lists);
    cur = merge;
    for (auto num : ans) {
        assert(cur != nullptr);
        assert(cur->val == num);
        cur = cur->next;
    }
    destoryList(merge);

    return 0;
}