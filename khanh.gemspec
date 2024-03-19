Gem::Specification.new do |s|
    s.name        = "khanh"
    s.version     = "0.0.6"
    s.summary     = "a collection of ruby methods operated in C env."
    s.description = "a ruby gem with an C extension from Khanh."
    s.authors     = ["Khanh"]
    s.email       = "dreamproperty.khanh@gmail.com"
    
    s.files       = [
      "lib/khanh.rb", 
      "ext/khanh/khanh.so",
      "lib/khanh/extension.rb"
    ]
    s.extensions = %w[ext/khanh/extconf.rb]
    
    s.metadata["allowed_push_host"] = "https://rubygems.org"
    s.metadata["homepage_uri"] = "https://github.com/khanh-devos/gem-cruby"
    
    s.license       = "MIT"
end

