//
//  HomeView.swift
//  Sample-AppleWatch Extension
//
//  Created by ubook on 26/04/21.
//  Copyright © 2021 PRSoluções. All rights reserved.
//

import Foundation
import SwiftUI
import WatchKit

struct HomeView: View {
    @ObservedObject private(set) var viewModel = HomeViewModel()
    
    private let mainColor = UIColor(hexString: "#ff3860")!
    private let rowBackgroundColor = UIColor(hexString: "#ffffff")!
    
    var body: some View {
        ZStack {
            NavigationLink(
                destination: Text("Destination"),
                isActive: $viewModel.showTodoList,
                label: {
                    EmptyView()
                }
            ).hidden()
            
            ZStack(alignment: .top) {
                List {
                    Section(
                        header: Rectangle()
                            .frame(height:26)
                            .foregroundColor(Color.clear)
                    ) {
                        ForEach(self.viewModel.listData, id: \.self) { item in
                            HStack {
                                Image(uiImage: item.getImage())
                                Text("\(item.getDescription())")
                                    .foregroundColor(Color(mainColor))
                            }
                            .onTapGesture {
                                viewModel.selectItem(item)
                            }
                            .listRowBackground(
                                RoundedRectangle(cornerRadius: 8)
                                    .foregroundColor(Color(rowBackgroundColor))
                            )
                        }
                    }
                }.listStyle(PlainListStyle())
                ZStack(alignment: .top) {
                    LinearGradient(gradient: Gradient(colors: [Color.black, Color.black, Color.black, Color.clear]), startPoint: .top, endPoint: .bottom)
                    Text("Home")
                        .font(.headline)
                        .foregroundColor(Color.pink)
                }
                .frame(height: 30)
            }
            
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