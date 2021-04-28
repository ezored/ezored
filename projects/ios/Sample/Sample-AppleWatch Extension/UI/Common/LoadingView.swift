//
//  LoadingView.swift
//  Sample-AppleWatch Extension
//
//  Created by ubook on 28/04/21.
//  Copyright © 2021 PRSoluções. All rights reserved.
//

import SwiftUI

struct LoadingView: View {
    var body: some View {
        ZStack(alignment: .center) {
            Rectangle()
                .foregroundColor(Color(UIColor.black.withAlphaComponent(0.1)))
            RoundedRectangle(cornerRadius: 8)
                .frame(width: 30, height: 30, alignment: .center)
                .foregroundColor(Color(UIColor(hexString: "#272727", alpha: 0.5)!))
            
        }
    }
}
