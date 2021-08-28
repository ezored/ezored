Pod::Spec.new do |s|    
  s.name             = '{NAME}'
  s.version          = '{VERSION}'
  s.summary          = '{NAME} pod'

  s.homepage         = 'https://github.com/ezored/ezored'
  s.license          = { :type => 'MIT', :text => 'Free' }
  s.author           = { 'Paulo Coutinho' => 'paulo@prsolucoes.com' }
  s.source           = { :http => 'https://ezored.s3.amazonaws.com/dist/ios/{VERSION}/dist.tar.gz' }  

  s.vendored_frameworks = 'Release/{NAME}.xcframework'

  s.ios.deployment_target = '9.0'
  s.watchos.deployment_target = '5.0'
  s.tvos.deployment_target = '11.0'

  s.public_header_files = 'Release/{NAME}.xcframework/{XCFRAMEWORK_RELEASE_GROUP_DIR}/{NAME}.framework/Headers/**/*.h'
  s.source_files = 'Release/{NAME}.xcframework/{XCFRAMEWORK_RELEASE_GROUP_DIR}/{NAME}.framework/Headers/**/*.h'

  s.requires_arc = true

  s.user_target_xcconfig = { 
    'USER_HEADER_SEARCH_PATHS' => '"$(PODS_ROOT)/{NAME}/Release" "$(PODS_ROOT)/{NAME}/Release/{NAME}.xcframework/{XCFRAMEWORK_RELEASE_GROUP_DIR}/{NAME}.framework/Headers"',
    'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/{NAME}/Release"'
  }
end
