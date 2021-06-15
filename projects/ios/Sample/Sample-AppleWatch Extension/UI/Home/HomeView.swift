
import Foundation
import SwiftUI
import WatchKit

struct HomeView: View {
    @ObservedObject private(set) var viewModel = HomeViewModel()
    
    private let mainColor = UIColor(hexString: "#D21601")!
    private let rowBackgroundColor = UIColor(hexString: "#332F2E")!
    
    var body: some View {
        ZStack {
            NavigationLink(
                destination: ToDoListView(),
                tag: ActionState.active,
                selection: $viewModel.showTodoList,
                label: {
                    EmptyView()
                }
            )
            
            ZStack(alignment: .top) {
                List {
                    Section(
                        header: Rectangle()
                            .frame(height:26)
                            .foregroundColor(Color.clear)
                    ) {
                        ForEach(self.viewModel.listData, id: \.self) { item in
                            Button {
                                viewModel.selectItem(item)
                            } label: {
                                HStack {
                                    Image(uiImage: item.getImage())
                                    Text("\(item.getDescription())")
                                        .foregroundColor(Color(mainColor))
                                }
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
                    Text("Home")
                        .font(.headline)
                        .foregroundColor(Color(hex: "#D21601"))
                }
                .frame(height: 30)
            }
            
            if let message = viewModel.alertMessage.data {
                AlertMessageView(message: message)
                    .onTapGesture {
                        viewModel.tapAlertMessage()
                    }
            }
            
            LoadingView()
                .isHidden(!viewModel.alertMessage.isLoading && !viewModel.showTodoList.isLoading)
        }
        .onAppear {
            DispatchQueue.main.async {
                self.viewModel.loadData()
            }
        }
    }
}

class HomeHostingController: WKHostingController<HomeView> {
    override var body: HomeView {
        return HomeView()
    }
}
