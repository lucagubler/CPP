#include <memory>

int * createVariableOnHeap() {
	return new int{};
}

int main() {
	int variableOnStack{23};
	auto pHeapVariable = createVariableOnHeap();
	delete pHeapVariable;
	
	auto uniqueInt = std::make_unique<int>();
}