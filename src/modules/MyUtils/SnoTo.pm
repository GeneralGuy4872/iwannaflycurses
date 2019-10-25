package MyUtils::SnoTo;

use warnings;
use strict;
use Filter::Simple;

FILTER_ONLY
	code_no_comments => sub { s/^(?:[\w]:)?[\s]*([\S]+(?:[\s]+[\S]+)*)[\s]+:\(([\w]+)\)$/$1; goto $2;/gm },
	code_no_comments => sub { s/^(?:[\w]:)?[\s]*([\S]+(?:[\s]+[\S]+)*)[\s]+:S\(([\w]+)\)$/if ($1) {goto $2};/gm },
	code_no_comments => sub { s/^(?:[\w]:)?[\s]*([\S]+(?:[\s]+[\S]+)*)[\s]+:F\(([\w]+)\)$/unless ($1) {goto $2};/gm },
	code_no_comments => sub { s/^(?:[\w]:)?[\s]*([\S]+(?:[\s]+[\S]+)*)[\s]+:S\(([\w]+)\)F\(([\w]+)\)$/if ($1) {goto $2} else {goto $3};/gm },
	code_no_comments => sub { s/^(?:[\w]:)?[\s]*([\S]+(?:[\s]+[\S]+)*)[\s]+:F\(([\w]+)\)S\(([\w]+)\)$/unless ($1) {goto $2} else {goto $3};/gm },
	code_no_comments => sub { s/«(.*?)»[\s]*:\(([\w]+)\)$/$1; goto $2;/gms },
	code_no_comments => sub { s/«(.*?)»[\s]*:S\(([\w]+)\)$/if ($1) {goto $2};/gms },
	code_no_comments => sub { s/«(.*?)»[\s]*:F\(([\w]+)\)$/unless ($1) {goto $2};/gms },
	code_no_comments => sub { s/«(.*?)»[\s]*:S\(([\w]+)\)F\(([\w]+)\)$/if ($1) {goto $2} else {goto $3};/gms },
	code_no_comments => sub { s/«(.*?)»[\s]*:F\(([\w]+)\)S\(([\w]+)\)$/unless ($1) {goto $2} else {goto $3};/gms },
	code_no_comments => sub { s/→([\w]+)/goto($1)/g };
