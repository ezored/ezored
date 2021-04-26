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
    var body: some View {
        Text("Home")
    }
}

class HomeHostingController: WKHostingController<HomeView> {
    override var body: HomeView {
        return HomeView()
    }
}
