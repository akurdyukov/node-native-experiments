{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "myobject.cc", "async.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
