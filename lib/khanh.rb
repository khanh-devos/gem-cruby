module Khanh
    class CRuby
        VERSION = "1.0"
        
        def self.hi
            p "Hello World!"
        end

    end

    def self.sort(arr)
        qSort(arr.join("-") + "-", arr.length)
    end
end


require_relative "khanh/extension"
require_relative "openssl/digest"
