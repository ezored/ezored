
import SwiftUI

class ToDoListViewModel: NSObject, ObservableObject {
    @Published var listData: [EZRDomainTodo] = []
    
    func loadData() {
        listData = EZRrepositoryTodoRepository.findAllOrderByCreatedAtDesc()
    }
    
    func selectItem(_ item: EZRDomainTodo) {
        guard let index = listData.firstIndex(of: item) else { return }
        EZRrepositoryTodoRepository.setDoneById(item.id, done: !item.done)
        listData[index] = EZRrepositoryTodoRepository.find(byId: item.id)
    }
}
