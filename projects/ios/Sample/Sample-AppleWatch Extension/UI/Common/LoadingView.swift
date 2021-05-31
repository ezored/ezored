
import SwiftUI

struct LoadingView: View {
    @State private var isRotating: Bool = false
    
    private var size: CGFloat = 60
    private var width: CGFloat = 2
    
    var body: some View {
        ZStack(alignment: .center) {
            Rectangle()
                .foregroundColor(Color(UIColor.black.withAlphaComponent(0.1)))
            
            RoundedRectangle(cornerRadius: 8)
                .frame(width: size, height: size, alignment: .center)
                .foregroundColor(Color(UIColor.black.withAlphaComponent(0.7)))
            
            Circle()
                .trim(from: 0.5, to: 1.0)
                .stroke(lineWidth: width)
                .foregroundColor(Color(UIColor(hexString: "#D21601")!))
                .rotationEffect(.degrees(isRotating ? 360 : 0))
                .frame(width: size * 0.75, height: size  * 0.75, alignment: .center)
                .onAppear {
                    withAnimation(Animation.linear(duration: 1).repeatForever(autoreverses: false)) {
                        self.isRotating.toggle()
                    }
                }
        }
    }
}
