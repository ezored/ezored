import Foundation

class BundleHelper {
    static func extract() {
        EZRLogger.i("[BundleHelper : extract] Starting bundle assets extraction...")

        let filemgr = FileManager.default
        let dirPaths = filemgr.urls(for: .documentDirectory, in: .userDomainMask)
        let docsURL = dirPaths[0]

        let folderPath = Bundle.main.resourceURL!.appendingPathComponent("webapp").path
        let docsFolder = docsURL.appendingPathComponent("webapp").path

        copyFiles(pathFromBundle: folderPath, pathDestDocs: docsFolder)

        EZRLogger.i("[BundleHelper : extract] Bundle assets extraction finished")
    }

    static func copyFiles(pathFromBundle: String, pathDestDocs: String) {
        let fileManagerIs = FileManager.default

        do {
            let filelist = try fileManagerIs.contentsOfDirectory(atPath: pathFromBundle)
            try? fileManagerIs.copyItem(atPath: pathFromBundle, toPath: pathDestDocs)

            for filename in filelist {
                try? fileManagerIs.copyItem(atPath: "\(pathFromBundle)/\(filename)", toPath: "\(pathDestDocs)/\(filename)")
            }
        } catch {
            EZRLogger.e("[BundleHelper : copyFiles] Error: \(error.localizedDescription)")
        }
    }
}
