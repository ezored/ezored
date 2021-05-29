import SwiftUI

struct AlertMessageView: View {
    let message: String
    
    var body: some View {
        GeometryReader { geometry in
            ScrollView(.vertical) {
                VStack {
                    Text("\(message)")
                        .foregroundColor(Color(UIColor(hexString: "#F44336")!))
                        .lineLimit(nil)
                        .padding(6)
                        .background(
                            RoundedRectangle(cornerRadius: 5)
                                .foregroundColor(Color(UIColor.white))
                                .shadow(color: .black, radius: 10, x: 5, y: 5)
                        )
                }
                .padding()
                .frame(width: geometry.size.width)      // Make the scroll view full-width
                .frame(minHeight: geometry.size.height) // Set the content’s min height to the parent
            }
        }
    }
}
