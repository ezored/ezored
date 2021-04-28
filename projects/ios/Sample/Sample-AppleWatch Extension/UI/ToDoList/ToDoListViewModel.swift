
import SwiftUI

class ToDoListViewModel: NSObject, ObservableObject {
    @Published var listData: [EZRDomainTodo] = []
    
    func loadData() {
        listData = EZRDataServicesTodoDataService.findAllOrderByCreatedAtDesc()
    }
    
    func selectItem(_ item: EZRDomainTodo) {
        guard let index = listData.firstIndex(of: item) else { return }
        EZRDataServicesTodoDataService.setDoneById(item.id, done: !item.done)
        listData[index] = EZRDataServicesTodoDataService.find(byId: item.id)
    }
}
