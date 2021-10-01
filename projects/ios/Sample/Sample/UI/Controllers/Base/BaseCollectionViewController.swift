import Foundation
import UIKit

class BaseCollectionViewController: BaseViewController, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout {
    var collectionView: UICollectionView!

    override func createAll() {
        super.createAll()

        collectionView = UICollectionView(frame: view.frame, collectionViewLayout: createCollectionViewLayout())
        collectionView.backgroundColor = .clear
        collectionView.dataSource = self
        collectionView.delegate = self
        collectionView.translatesAutoresizingMaskIntoConstraints = false
        collectionView.contentInset = getCollectionViewContentInset()

        let tapGesture = UITapGestureRecognizer(target: self, action: #selector(onCollectionViewTappedChecker))
        tapGesture.numberOfTapsRequired = 1
        collectionView.addGestureRecognizer(tapGesture)

        view.addSubview(collectionView)

        registerCollectionViewCells()
    }

    override func layoutAll() {
        super.layoutAll()

        // collection view
        view.addConstraint(NSLayoutConstraint(item: collectionView!, attribute: .centerX, relatedBy: .equal, toItem: view, attribute: .centerX, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: collectionView!, attribute: .centerY, relatedBy: .equal, toItem: view, attribute: .centerY, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: collectionView!, attribute: .width, relatedBy: .equal, toItem: view, attribute: .width, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: collectionView!, attribute: .height, relatedBy: .equal, toItem: view, attribute: .height, multiplier: 1.0, constant: 0.0))
    }

    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return onCollectionViewGetNumberOfItems(collectionView: collectionView, section: section)
    }

    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = onCollectionViewCreateCell(collectionView: collectionView, indexPath: indexPath)
        bindEventsOnCell(cell: cell, index: Int(indexPath.row))
        return cell
    }

    func collectionView(_ collectionView: UICollectionView, willDisplay _: UICollectionViewCell, forItemAt indexPath: IndexPath) {
        if indexPath.row > 0, indexPath.row == getTotalOfItems() - 1 {
            onCollectionViewReachLastItem(collectionView: collectionView, indexPath: indexPath)
        }
    }

    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        onCollectionViewSelectedCell(collectionView: collectionView, indexPath: indexPath)
    }

    func bindEventsOnCell(cell: UICollectionViewCell, index _: Int) {
        let longPressGesture = UILongPressGestureRecognizer(target: self, action: #selector(onCellLongPressGesture))
        cell.addGestureRecognizer(longPressGesture)
    }

    override func networkErrorViewProtocolOnAction(action: NetworkErrorViewAction) {
        super.networkErrorViewProtocolOnAction(action: action)

        if action == .refresh {
            if remoteDataLoadState != .loading {
                remoteDataLoadState = .notLoaded
            }

            loadData()
        }
    }

    override func getVCTitle() -> String {
        return "BaseCollectionView"
    }

    @objc func onCellLongPressGesture(sender: UILongPressGestureRecognizer) {
        if sender.state != .began {
            return
        }

        let tapLocation = sender.location(in: collectionView)

        if let indexPath = collectionView?.indexPathForItem(at: tapLocation) {
            onCellLongPress(indexPath: indexPath)
        }
    }

    func createCollectionViewLayout() -> UICollectionViewFlowLayout {
        let layout = UICollectionViewFlowLayout()
        layout.itemSize = getCollectionViewItemSize()

        return layout
    }

    func registerCollectionViewCells() {}

    // MARK: EVENTS

    func onCellLongPress(indexPath _: IndexPath) {
        // will be implemented on child
    }

    @objc func onCollectionViewTappedChecker(sender: UITapGestureRecognizer) {
        if let indexPath = collectionView.indexPathForItem(at: sender.location(in: collectionView)) {
            onCollectionViewSelectedCell(collectionView: collectionView, indexPath: indexPath)
        } else {
            onCollectionViewTapped()
        }
    }

    func onCollectionViewSelectedCell(collectionView _: UICollectionView, indexPath _: IndexPath) {
        // will be implemented on child
    }

    func onCollectionViewTapped() {
        dismissKeyboard()
    }

    func getCollectionViewItemSize() -> CGSize {
        return CGSize(width: 120, height: 230)
    }

    func getCollectionViewContentInset() -> UIEdgeInsets {
        return UIEdgeInsets(top: 20, left: 20, bottom: 20, right: 20)
    }

    func onCollectionViewCreateCell(collectionView _: UICollectionView, indexPath _: IndexPath) -> UICollectionViewCell {
        // will be implemented on child
        return UICollectionViewCell()
    }

    func onCollectionViewGetNumberOfItems(collectionView _: UICollectionView, section _: Int) -> Int {
        return getTotalOfItems()
    }

    func getTotalOfItems() -> Int {
        // will be implemented on child
        return 0
    }

    func onCollectionViewReachLastItem(collectionView _: UICollectionView, indexPath _: IndexPath) {
        // will be implemented on child
    }

    // MARK: CACHE

    override func onCacheExpired() {
        super.onCacheExpired()

        if remoteDataLoadState != .loading {
            remoteDataLoadState = .notLoaded
        }

        loadData()
    }
}
