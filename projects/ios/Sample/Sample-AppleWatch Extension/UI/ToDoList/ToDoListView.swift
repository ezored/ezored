
import SwiftUI

struct ToDoListView: View {
    @ObservedObject private(set) var viewModel = ToDoListViewModel()
    
    private let mainColor = UIColor(hexString: "#D21601")!
    private let rowBackgroundColor = UIColor(hexString: "#332F2E")!
    
    var body: some View {
        ZStack(alignment: .top) {
            List {
                Section(
                    header: Rectangle()
                        .frame(height:26)
                        .foregroundColor(Color.clear)
                ) {
                    ForEach(viewModel.listData, id: \.self) { item in
                        Button {
                            viewModel.selectItem(item)
                        } label: {
                            HStack(alignment: .top, spacing: 5) {
                                Image(uiImage: UIImage(named: item.done ? "IcoItemOn" : "IcoItemOff")!.imageWithColor(color: mainColor)!)
                                VStack(alignment: .leading, spacing: 2) {
                                    Text("ID: \(item.id)")
                                    Text("Title: \(item.title)")
                                    Text("Body: \(item.body)")
                                    Text("Created at: \(DateTimeHelper.formatAsMysql(date: item.createdAt))")
                                }
                                .foregroundColor(Color(mainColor))
                            }
                            .padding(EdgeInsets.init(top: 5, leading: 0, bottom: 5, trailing: 0))
                        }
                        .listRowBackground(
                            RoundedRectangle(cornerRadius: 8)
                                .foregroundColor(Color(rowBackgroundColor))
                        )
                    }
                }
            }
            ZStack(alignment: .top) {
                LinearGradient(gradient: Gradient(colors: [Color.black, Color.black, Color.black, Color.clear]), startPoint: .top, endPoint: .bottom)
                Text("ToDo")
                    .font(.headline)
                    .foregroundColor(Color(hex: "#D21601"))
            }
            .frame(height: 30)
        }
        .onAppear {
            DispatchQueue.main.async {
                viewModel.loadData()
            }
        }
    }
}
