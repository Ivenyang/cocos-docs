# Wiki宏列表
`child_pages`

显示子页面，没有参数时，现实当前wiki的子节点。例如：

	{{child_pages}} -- can be used from a wiki page only
	{{child_pages(Foo)}} -- lists all children of page Foo
	{{child_pages(Foo, parent=1)}} -- same as above with a link to page Foo

`comment_form`

显示注释表

`comments`

显示当前页面的所有注释

`contact`

通过头像联系

`contact_avatar`

联系人头像

`contact_plain`

联系人描述

`count`

访问页面数

	{{count}}

`deal`

处理

`div_end_tag`

显示 `<pre></div></pre>`

	{{div_end_tag}}

`div_start_tag`

显示 `<pre><div id="id_name" class="class_name"></pre>`

	{{div_start_tag(id_name)}}'
	{{div_start_tag(id_name, class_name)}}

`fn`

创建脚注

	{{fn(word, description}}

`fnlist`

显示页面脚注

`hello_world`

简单宏

`iframe`

插入iframe

	{{iframe(url, width, height)}}

`include`

包含一个wiki页面。比如：

	{{include(Foo)}}

或者包含一个指定project的wiki:

	{{include(projectname:Foo)}}

`lastupdated_at`

显示最新更新日期

	{{lastupdated_at}}

`lastupdated_by`

显示更新页面的人

	{{lastupdated_by}}

`macro_list`

显示所有有效的宏，包含有效的描述

`new`

显示`new`字符串

	{{new(yyyy-mm-dd)}}
	{{new(yyyy-mm-dd, expire)}}

默认的expire的值为5

`popularity`

显示访问次数多的页面

	{{popularity}}
	{{popularity(max)}}
	{{popularity(max, term)}}

`project`

创建另外的项目的链接。

	{{project(project_name)}}
	{{project(project_identifire}}
	{{project(project_name, alias)}}
	{{project(project_identifire, alias}}

`recent`

显示最近改变的页面

	{{recent}}'
	{{recent(number_of_days)}}

`ref_issues`

显示参考issues列表

`show_count`

显示当前页面访问次数

	{{show_count}}

`show_vote`

显示投票结果

	{{show_vote(key)}}

`tagcloud`

显示标签云

	{{tagcloud}}

`taggedpages`

显示有特殊标签的页面

	{{taggedpages(tagname)}}
	{{taggedpages(tagname, project)}}

`tags`

显示标签

	{{tags}}

`thumbnails`

缩略图

`twitter`

创建twitter账号页面的链接

	{{twitter(user_name)}}

`vote`

投票宏

	{{vote(key)}}
	{{vote(key, label)}}

`wiki`

创建到其他工程wiki页面的链接

	{{wiki(project_name, wiki_page)}}
	{{wiki(project_name, wiki_page, alias)}}
	{{wiki(project_identifier, wiki_page)}}
	{{wiki(project_identifier, wiki_page, alias)}}