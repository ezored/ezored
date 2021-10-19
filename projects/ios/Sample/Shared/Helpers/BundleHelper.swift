import Foundation

class BundleHelper {
    static func extract() {
        EZRLogger.i("[BundleHelper : extract] Starting bundle assets extraction...")

        let fm = FileManager.default
        let dirPaths = fm.urls(for: .documentDirectory, in: .userDomainMask)
        let docsURL = dirPaths[0]

        let folderPath = Bundle.main.resourceURL!.appendingPathComponent("webapp").path
        let docsFolder = docsURL.appendingPathComponent("webapp").path

        EZRFileHelper.removeDir(docsFolder)

        copyFiles(pathFromBundle: folderPath, pathDestDocs: docsFolder)

        EZRLogger.i("[BundleHelper : extract] Bundle assets extraction finished")
    }

    static func copyFiles(pathFromBundle: String, pathDestDocs: String) {
        let fm = FileManager.default

        do {
            let filelist = try fm.contentsOfDirectory(atPath: pathFromBundle)
            try? fm.copyItem(atPath: pathFromBundle, toPath: pathDestDocs)

            for filename in filelist {
                try? fm.copyItem(atPath: "\(pathFromBundle)/\(filename)", toPath: "\(pathDestDocs)/\(filename)")
            }
        } catch {
            EZRLogger.e("[BundleHelper : copyFiles] Error: \(error.localizedDescription)")
        }
    }
}
