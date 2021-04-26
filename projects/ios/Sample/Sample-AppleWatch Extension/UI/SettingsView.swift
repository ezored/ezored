//
//  SettingsView.swift
//  Sample-AppleWatch Extension
//
//  Created by ubook on 26/04/21.
//  Copyright © 2021 PRSoluções. All rights reserved.
//

import Foundation
import SwiftUI
import WatchKit

struct SettingsView: View {
    var body: some View {
        Text("Settings")
    }
}

class SettingsHostingController: WKHostingController<SettingsView> {
    override var body: SettingsView {
        return SettingsView()
    }
}
