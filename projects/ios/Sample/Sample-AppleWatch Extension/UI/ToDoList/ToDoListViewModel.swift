
import SwiftUI

class ToDoListViewModel: NSObject, ObservableObject {
    @Published var listData: [EZRDomainTodo] = []
    
    func loadData() {
        listData = EZRRepositoryTodoRepository.findAllOrderByCreatedAtDesc()
    }
    
    func selectItem(_ item: EZRDomainTodo) {
        guard let index = listData.firstIndex(of: item) else { return }
        EZRRepositoryTodoRepository.setDoneById(item.id, done: !item.done)
        listData[index] = EZRRepositoryTodoRepository.find(byId: item.id)
    }
}
