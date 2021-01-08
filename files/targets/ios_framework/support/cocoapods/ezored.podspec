Pod::Spec.new do |s|    
  s.name             = 'ezored'
  s.version          = '1.0.0'
  s.summary          = 'ezored pod'

  s.homepage         = 'https://github.com/ezored/ezored'
  s.license          = { :type => 'MIT', :text => 'Free' }
  s.author           = { 'Paulo Coutinho' => 'paulo@prsolucoes.com' }
  s.source           = { :http => 'https://ezored.s3.amazonaws.com/dist/ios_framework/1.0.0/dist.tar.gz' }  

  s.vendored_frameworks = 'Release/ezored.xcframework'

  s.ios.deployment_target = '9.0'

  s.public_header_files = 'Release/ezored.xcframework/ios-arm64_arm64e_armv7_armv7s/ezored.framework/Headers/**/*.h'
  s.source_files = 'Release/ezored.xcframework/ios-arm64_arm64e_armv7_armv7s/ezored.framework/Headers/**/*.h'

  s.requires_arc = true

  s.user_target_xcconfig = { 
    'USER_HEADER_SEARCH_PATHS' => '"$(PODS_ROOT)/ezored/Release" "$(PODS_ROOT)/ezored/Release/ezored.xcframework/ios-arm64_arm64e_armv7_armv7s/ezored.framework/Headers"',
    'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/ezored/Release"'
  }
end
