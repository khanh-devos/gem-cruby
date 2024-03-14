Gem::Specification.new do |s|
    s.name        = "khanh"
    s.version     = "0.0.4"
    s.summary     = "a collection of ruby methods operated in C"
    s.description = "C-ruby from Khanh"
    s.authors     = ["Khanh"]
    s.email       = "dreamproperty.khanh@gmail.com"
    
    s.files       = [
      "lib/khanh.rb", 
      "ext/khanh/khanh.so",
      "lib/khanh/extension.rb"
    ]
    s.extensions = %w[ext/khanh/extconf.rb]
    
    s.homepage    =
      "https://github.com/khanh-devos/gem-cruby"
    
    s.license       = "MIT"
end